#pragma once
#include "Vector2.h"

namespace CPhysics 
{
	struct Circle 
	{
		Circle();
		Circle(float x, float y, float radius);
		Circle(Vector2 pos, float radius);
		Vector2 position;
		float radius;
	};
}