#pragma once

#include "Rectangle.h"
#include "Circle.h"
#include "Vector2.h"
#include "Tension.h"

#include <vector>

namespace CPhysics
{
	//forward declerations
	class CollisionObject;
	struct Collision;


	struct PhysicsObjectProperties
	{
		float mass = 1.0f;
		float bounciness = 0.8f;

		float drag = 20.0f;


		bool isStatic = false;
		bool doCollision = true;
	};
	class PhysicsObject
	{
	public:
		PhysicsObject(PhysicsObjectProperties objProp, CollisionObject* colObj);

		static void update(float dt);

		void updatePosition(float dt);

		//Getters
		PhysicsObjectProperties& getProp() { return prop; }
		CollisionObject& getCollisionObject() { return *colObj; }
		Vector2 getVelocity() const { return velocity; }
		Vector2 getPosition() const;
		Vector2 getSize() const;


		//setters
		void setVelocity(Vector2 newVel) { velocity = newVel; }
		void changeVelocity(Vector2 delta) { velocity+=delta; }
		
		static void addTension(Tension* tension) { TensionConnectors.push_back(tension); }
	private:
		PhysicsObjectProperties prop;
		CollisionObject* colObj = nullptr;
		Vector2 velocity;
		inline static std::vector<PhysicsObject*> physicObjects; 
		inline static std::vector<Tension*> TensionConnectors;

	};
}
