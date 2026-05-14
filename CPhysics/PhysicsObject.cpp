#include "PhysicsObject.h"
#include "CollisionObject.h"
#include <iostream>
namespace CPhysics
{
	PhysicsObject::PhysicsObject(PhysicsObjectProperties objProp, std::vector<Rectangle*> colRects, std::vector<Circle*> colCircles) : prop(objProp), CollisionObject(colRects,colCircles)
	{
		physicObjects.push_back(this);
	}

	void PhysicsObject::update(float dt)
	{
		//Collision Implementation 
		PhysicsObject* objA;
		PhysicsObject* objB;
		for (int i = 0; i < physicObjects.size(); i++)
		{
			objA = physicObjects.at(i);
			if (objA->prop.doCollision)
			{
				for (int j = i + 1; j < physicObjects.size(); j++)
					{
						objB = physicObjects.at(j);
						if (objB->prop.doCollision)
						{

							Collision collision = CollisionObject::checkCollision(objA,objB);
							if (collision.collision)
							{
								//There is a collision so now I have to implement the bounce formula 676767667676767

								Vector2 relVel = objB->velocity - objA->velocity;

								float NormalVel = Vector2::Dot(relVel,collision.collisionNormal);
					
								if (NormalVel > 0) continue;
								PhysicsObjectProperties& AProp = objA->prop;
								PhysicsObjectProperties& BProp = objB->prop;

								float AImpulse = (NormalVel * -(1+AProp.bounciness)) / (1 / AProp.mass + 1 / BProp.mass);
								float BImpulse = (NormalVel * -(1+BProp.bounciness)) / (1 / AProp.mass + 1 / BProp.mass);

								objA->velocity += collision.collisionNormal * -AImpulse / AProp.mass;
								objB->velocity += collision.collisionNormal *  BImpulse / BProp.mass;

							}
							
						}
						
					}
			}
		}


		//Tension Implementation
		/*for (Tension* tension : TensionConnectors) 
		{
			tension->ApplyTension(dt);
		}*/ //depricated


		//Drag Implementation
		for (PhysicsObject* obj : physicObjects)
		{
			if (!obj->prop.isStatic)
			{

				Vector2 dragForce = obj->velocity * -obj->prop.drag/obj->prop.mass;
				obj->changeVelocity(dragForce * dt);
			}
		}

		//Update 
		for (PhysicsObject* obj : physicObjects)
		{
			if (!obj->prop.isStatic)
			{
				obj->updatePosition(dt);
			}
		}
		
	}

	void PhysicsObject::updatePosition(float dt)
	{
		position += velocity * dt;
	}


	Vector2 PhysicsObject::getPosition() const {return position;}
	Vector2 PhysicsObject::getVelocity() const {return velocity;}

}

