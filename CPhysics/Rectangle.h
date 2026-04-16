#pragma once
#include "Vector2.h"
namespace CPhysics
{
	class Rectangle 
	{
	public:
		Vector2 topLeft, topRight, bottomLeft, bottomRight;

		Rectangle(){}

		Rectangle(float x, float y, float width, float height) 
		{
			origin = Vector2(x, y);
			size = Vector2(width, height);
			calculateCorners();

		}

		Rectangle(Vector2 position, Vector2 size) : origin(position), size(size)
		{
			calculateCorners();
		}

		void changePosition(Vector2 delta) 
		{
			origin += delta;
			calculateCorners();
		}

	private:
		void calculateCorners() 
		{
			topLeft = origin - size / 2;
			topRight = origin + Vector2(size.x, -size.y)/2;
			bottomLeft = origin + Vector2(-size.x, size.y) / 2;
			bottomRight = origin + size / 2;
		}

		Vector2 origin, size;

	};
}
