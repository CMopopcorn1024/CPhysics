#pragma once
#include "Vector2.h"
#include "Segment.h"
#include <cmath>
#include <array>

namespace CPhysics
{
	class Rectangle 
	{
	public:
		Vector2 topLeft, topRight, bottomLeft, bottomRight;
		
		Segment top, bottom, left, right;	

		float rotation = 0;

		std::array<Vector2, 4> getVertices() const 
		{
			return {topLeft, topRight, bottomLeft, bottomRight};
		}

		std::array<Segment, 4> getSegments() const
		{
			return { top, bottom, left, right };
		}

		Rectangle(){}

		Rectangle(float x, float y, float width, float height, float rot = 0) 
		{
			origin = Vector2(x, y);
			size = Vector2(width, height);
			rotation = rot;
			calculate();

		}

		Rectangle(Vector2 position, Vector2 size, float rotation = 0) : origin(position), size(size), rotation(rotation)
		{
			calculate();
		}

		void changePosition(Vector2 delta) 
		{
			origin += delta;
			calculate();
		}

		void getMinMaxOnProjectionAxis(Vector2 axis,float& min, float& max) const 
		{
			std::array<Vector2, 4> vertices = getVertices();

			min = max = Vector2::Dot(vertices[0], axis);

			for (int i = 1; i < vertices.size(); i++) 
			{
				float projection = Vector2::Dot(vertices[i], axis);
				if (projection < min) min = projection;
				if (projection > max) max = projection;
			}
		}


		Vector2 getClosestPoint(Vector2 point)  const
		{
			std::array<Segment, 4> edges = getSegments();
			
			float min = Vector2::Distance(point, edges[0].getClosestPoint(point));
			Vector2 closestPoint = edges[0].getClosestPoint(point);

			for (int i = 1; i < edges.size(); i++) 
			{
				Vector2 closePoint = edges[i].getClosestPoint(point);
				float distance = Vector2::Distance(closePoint, point);
				if (distance < min) 
				{
					min = distance;
					closestPoint = closePoint;
				}
			}

			return closestPoint;
		}

		Vector2 getPosition() const { return origin; }
		Vector2 getSize() const { return size; }

	private:
		void calculate() 
		{
			Vector2 half = size * 0.5f;

			topLeft = Vector2::RotateAboutPoint(origin + Vector2(-half.x, -half.y), origin, rotation);
			topRight = Vector2::RotateAboutPoint(origin + Vector2(half.x, -half.y), origin, rotation);
			bottomLeft = Vector2::RotateAboutPoint(origin + Vector2(-half.x, half.y), origin, rotation);
			bottomRight = Vector2::RotateAboutPoint(origin + Vector2(half.x, half.y), origin, rotation);
			
			
			top.start = topLeft;
			top.end = topRight;

			bottom.start = bottomLeft;
			bottom.end = bottomRight;

			left.start = topLeft;
			left.end = bottomLeft;

			right.start = topRight;
			right.end = bottomRight;
		}

		Vector2 origin, size;

	};
}
