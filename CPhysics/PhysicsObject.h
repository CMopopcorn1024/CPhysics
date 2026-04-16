#pragma once

#include "Rectangle.h"
#include "Circle.h"

namespace CPhysics
{
	struct PhysicsObjectProperties
	{
		float mass;
		
		bool isStatic = false;
		bool doCollision = true;
		
		bool isRect = false;
		bool isCircle = false;

	};
	class PhysicsObject
	{
	public:
		PhysicsObject(PhysicsObjectProperties objProp, Rectangle colRect);
		PhysicsObject(PhysicsObjectProperties objProp, Circle colCircle);

		//Getters
		PhysicsObjectProperties& getProp() {return prop;}

	private:
		PhysicsObjectProperties prop;
		Rectangle colRect;
		Circle colCircle;
	};
}
