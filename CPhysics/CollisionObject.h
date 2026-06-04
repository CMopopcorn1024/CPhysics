#pragma once

#include <vector>
#include "Rectangle.h"
#include "Circle.h"
#include "Vector2.h"

namespace CPhysics
{
	struct Collision
	{
		bool collision = false;
		Vector2 collisionNormal;

	};

	class CollisionObject
	{
	public:
		CollisionObject(std::vector<Rectangle*> colRects, std::vector<Circle*> colCircles);

		CollisionObject() = default;

		static Collision checkCollision(CollisionObject* objA, CollisionObject* objB);

		static bool CircleCollision(const Circle* circleA, const Circle* circleB, Vector2& collisionNormal);

		static bool RectangleCircleCollision(const Rectangle* rect, const Circle* circle, Vector2& collisionNormal);

		static bool SATRectCollision(const Rectangle* rectA, const Rectangle* rectB, Vector2& collisionNormal);
		
		
	protected:
		Vector2 position;
		std::vector<Rectangle*> rects;
		std::vector<Circle*> circles;
	};
}