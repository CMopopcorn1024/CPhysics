#pragma once
#include "Rectangle.h"
#include "Circle.h"
#include "Vector2.h"
#include "PhysicsObject.h"

namespace CPhysics
{
	struct Collision
	{
		bool collision = false;
		PhysicsObject* objA = nullptr;
		PhysicsObject* objB = nullptr;
		Vector2 collisionNormal;
		Collision(PhysicsObject* objA, PhysicsObject* objB) : objA(objA), objB(objB) {}

	};

	class CollisionObject
	{
	public:
		CollisionObject(Rectangle* colRect);
		CollisionObject(Circle* colCircle);

		static Collision checkCollision(PhysicsObject* objA, PhysicsObject* objB);

		static bool CircleCollision(const Circle& circleA, const Circle& circleB, Vector2& collisionNormal);

		static bool RectangleCircleCollision(const Rectangle* rect, const Circle* circle, Vector2& collisionNormal);

		static bool SATRectCollision(const Rectangle* rectA, const Rectangle* rectB, Vector2& collisionNormal);


		bool isRect() const { return rect != nullptr; }
		bool isCircle() const { return circle != nullptr; }

		Rectangle* getRect() const { return rect; }
		Circle* getCircle() const { return circle; }

		void ChangePosition(Vector2 delta) 
		{
			if (isRect()) rect->changePosition(delta);
			if (isCircle()) circle->position += delta;
		}

		Vector2 getPosition() const 
		{
			if (isRect()) return rect->getPosition();
			if (isCircle()) return circle->position;
			return Vector2(0, 0);
		}

	private:
		Rectangle* rect = nullptr;
		Circle* circle = nullptr;
	};
}