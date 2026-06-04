#pragma once

#include "CollisionObject.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Vector2.h"
//#include "Tension.h" depricated 

#include <vector>

namespace CPhysics
{
	//forward declerations


	struct PhysicsObjectProperties
	{
		float mass = 1.0f;
		float bounciness = 0.8f;

		float drag = 20.0f;


		bool isStatic = false;
		bool doCollision = true;
	};
	class PhysicsObject : public CollisionObject
	{
	public:
		PhysicsObject() = default;
		PhysicsObject(PhysicsObjectProperties objProp, std::vector<Rectangle*> colRects, std::vector<Circle*> colCircles);

		static void update(float dt);

		void updatePosition(float dt);

		//Getters
		Vector2 getVelocity() const;
		Vector2 getPosition() const;

		

		//setters
		void setVelocity(Vector2 newVel) { velocity = newVel; }
		void changeVelocity(Vector2 delta) { velocity+=delta; }

		
		//static void addTension(Tension* tension) { TensionConnectors.push_back(tension); } depricated
	protected:
		PhysicsObjectProperties prop;
		Vector2 velocity;
	private:
		
		inline static std::vector<PhysicsObject*> physicObjects; 
		//inline static std::vector<Tension*> TensionConnectors; depricated

	};
}
