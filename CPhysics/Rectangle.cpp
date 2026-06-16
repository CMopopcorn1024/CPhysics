#include "Rectangle.h"

#include <iostream>
namespace CPhysics
{
	std::array<Vector2, 4> Rectangle::getVertices() const
	{
		return { topLeft, topRight, bottomLeft, bottomRight };
	}

	std::array<Segment, 4> Rectangle::getSegments() const
	{
		return { top, bottom, left, right };
	}

	Rectangle::Rectangle(float x, float y, float width, float height, float rot)
	{
		origin = Vector2(x, y);
		size = Vector2(width, height);
		rotation = rot;
		calculate();

	}

	Rectangle::Rectangle(Vector2 position, Vector2 size, float rotation) : origin(position), size(size), rotation(rotation)
	{
		calculate();
	}

	void Rectangle::changePosition(Vector2 delta)
	{
		origin += delta;
		calculate();
	}

	void Rectangle::getMinMaxOnProjectionAxis(Vector2 axis, float& min, float& max) const
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

	Vector2 Rectangle::getClosestPoint(Vector2 point)  const
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

	void Rectangle::calculate()
	{

		Vector2 half = size * 0.5f;

		Vector2 pos = getPosition();

		topLeft = Vector2::RotateAboutPoint(pos + Vector2(-half.x, -half.y), pos, rotation);
		topRight = Vector2::RotateAboutPoint(pos + Vector2(half.x, -half.y), pos, rotation);
		bottomLeft = Vector2::RotateAboutPoint(pos + Vector2(-half.x, half.y), pos, rotation);
		bottomRight = Vector2::RotateAboutPoint(pos + Vector2(half.x, half.y), pos, rotation);


		top.start = topLeft;
		top.end = topRight;

		bottom.start = bottomLeft;
		bottom.end = bottomRight;

		left.start = topLeft;
		left.end = bottomLeft;

		right.start = topRight;
		right.end = bottomRight;
	}

	Vector2 Rectangle::getPosition() const 
	{ 
		return origin; 
	}
}