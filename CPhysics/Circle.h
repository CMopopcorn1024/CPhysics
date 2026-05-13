#pragma once
#include "Vector2.h"

namespace CPhysics 
{
	struct Circle 
	{
		Circle() : position(0, 0), radius(1) {}
		Circle(float x, float y, float radius) : position(x, y), radius(radius) {}
		Circle(Vector2 pos, float radius) : position(pos), radius(radius) {}
		Vector2 position;
		float radius;
	};
}