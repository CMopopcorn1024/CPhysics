#include "PhysicsObject.h"
#include "CollisionObject.h"
#include <iostream>
namespace CPhysics
{
	PhysicsObject::PhysicsObject(PhysicsObjectProperties objProp, CollisionObject* colObj) : prop(objProp), colObj(colObj)
	{
		physicObjects.push_back(this);
	}

	void PhysicsObject::update(float dt)
	{
		//Collision Implementation 

		for (int i = 0; i < physicObjects.size(); i++)
		{
			if (physicObjects.at(i)->getProp().doCollision)
			{
				for (int j = i + 1; j < physicObjects.size(); j++)
					{
						if (physicObjects.at(i)->getProp().doCollision)
						{

							Collision collision = CollisionObject::checkCollision(physicObjects.at(i), physicObjects.at(j));
							if (collision.collision)
							{
								//There is a collision so now I have to implement the bounce formula 676767667676767

								Vector2 relVel = collision.objB->velocity - collision.objA->velocity;

								float NormalVel = Vector2::Dot(relVel,collision.collisionNormal);
					
								if (NormalVel > 0) continue;
								PhysicsObjectProperties& AProp = collision.objA->getProp();
								PhysicsObjectProperties& BProp = collision.objB->getProp();

								float AImpulse = (NormalVel * -(1+AProp.bounciness)) / (1 / AProp.mass + 1 / BProp.mass);
								float BImpulse = (NormalVel * -(1+BProp.bounciness)) / (1 / AProp.mass + 1 / BProp.mass);

								collision.objA->changeVelocity(collision.collisionNormal * -AImpulse / AProp.mass);
								collision.objB->changeVelocity(collision.collisionNormal * BImpulse / BProp.mass);

							}
							
						}
						
					}
			}
		}


		//Tension Implementation
		for (Tension* tension : TensionConnectors) 
		{
			tension->ApplyTension(dt);
		}


		//Drag Implementation
		for (PhysicsObject* obj : physicObjects)
		{
			if (!obj->getProp().isStatic)
			{
				PhysicsObjectProperties* prop = &obj->getProp();

				Vector2 dragForce = obj->velocity * -prop->drag/prop->mass;
				obj->changeVelocity(dragForce * dt);
			}
		}

		//Update 
		for (PhysicsObject* obj : physicObjects)
		{
			if (!obj->getProp().isStatic)
			{
				obj->updatePosition(dt);
			}
		}
		
	}

	void PhysicsObject::updatePosition(float dt)
	{
		colObj->ChangePosition(velocity * dt);
	}

	Vector2 PhysicsObject::getPosition() const
	{
		return colObj->getPosition();
	}

	Vector2 PhysicsObject::getSize() const
	{
		if (colObj->isRect()) return colObj->getRect()->getSize();
		if (colObj->isCircle()) return Vector2(colObj->getCircle()->radius, colObj->getCircle()->radius);
		return Vector2(0, 0);
	}

}

