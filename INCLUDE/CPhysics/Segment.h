#pragma once

#include "Vector2.h"
#include <algorithm>
namespace CPhysics
{
	struct Segment
	{
		Vector2 start;
		Vector2 end;

		Vector2 getClosestPoint(Vector2 point) const;

		Vector2 getEdgeNormal() const;
	};
}