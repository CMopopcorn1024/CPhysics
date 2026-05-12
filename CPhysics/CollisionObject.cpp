#include "CollisionObject.h"	
#include <iostream>
namespace CPhysics
{
	CollisionObject::CollisionObject(Rectangle* colRect) : rect(colRect) {}
	CollisionObject::CollisionObject(Circle* colCircle) : circle(colCircle) {}

	Collision CollisionObject::checkCollision(PhysicsObject* objA, PhysicsObject* objB)
	{
		Collision collision(objA, objB);
		
		CollisionObject& colObjA = objA->getCollisionObject();
		CollisionObject& colObjB = objB->getCollisionObject();

		bool objAIsRect = colObjA.isRect();
		bool objBIsRect = colObjB.isRect();


		if (objAIsRect == colObjA.isCircle() || objBIsRect == colObjB.isCircle())
		{
			return collision;
		}

		if (!objAIsRect && !objBIsRect) 
		{//Circle Collision
			collision.collision = CircleCollision(*colObjA.getCircle(), *colObjB.getCircle(), collision.collisionNormal);
		}
		else if (objAIsRect != objBIsRect) 
		{//One Rect Collision

			Rectangle* rect = (objAIsRect)? colObjA.getRect() : colObjB.getRect();
			Circle* circle = (objAIsRect) ? colObjB.getCircle() : colObjA.getCircle();
			collision.collision = RectangleCircleCollision(rect, circle, collision.collisionNormal);
		}
		else 
		{//2 Rect Collision 
			collision.collision = SATRectCollision(colObjA.getRect(), colObjB.getRect(), collision.collisionNormal);
		}

		return collision;
	}

	bool CollisionObject::CircleCollision(const Circle& circleA, const Circle& circleB, Vector2& collisionNormal)
	{
		Vector2 delta = circleB.position - circleA.position;
		float distance = delta.length();
		float radiusSum = circleA.radius + circleB.radius;
		if (distance < radiusSum)
		{
			collisionNormal = delta.Normalized();
			return true;
		}
		return false;
	}

	bool CollisionObject::RectangleCircleCollision(const Rectangle* rect, const Circle* circle, Vector2& collisionNormal)
	{
		Vector2 closestPoint = rect->getClosestPoint(circle->position);
		Vector2 delta = circle->position - closestPoint;
		float distance = delta.length();
		if (distance < circle->radius) 
		{
			collisionNormal = delta.Normalized();
			return true;
		}
		return false;
	}

	bool CollisionObject::SATRectCollision(const Rectangle* rectA, const Rectangle* rectB, Vector2& collisionNormal)
	{
		std::array<Vector2, 4> axes = {
			rectA->top.getEdgeNormal(),
			rectA->left.getEdgeNormal(),
			rectB->top.getEdgeNormal(),
			rectB->left.getEdgeNormal(),
		};


	
		float minOverlap = std::numeric_limits<float>::max();
		Vector2 smallestAxis;

		for (int i = 0; i < axes.size(); i++)
		{
			Vector2 axis = axes[i].Normalized();
			if (axis.x == 0 && axis.y == 0) continue;
			float minA, maxA, minB, maxB;
			rectA->getMinMaxOnProjectionAxis(axis, minA, maxA);
			rectB->getMinMaxOnProjectionAxis(axis, minB, maxB);
			

			
			float overlap = std::min(maxA, maxB) - std::max(minA, minB);
				
			if (overlap <= 0)
			{
				return false; 
			}

			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				smallestAxis = axis;
			}
			
		}


		Vector2 centerA = rectA->getPosition();
		Vector2 centerB = rectB->getPosition();

		Vector2 direction = centerB - centerA;

		if (Vector2::Dot(direction, smallestAxis) < 0)
		{
			smallestAxis = smallestAxis * -1.0f;
		}
		collisionNormal = smallestAxis;

		return true;
	}

}