#pragma once

#include "Vector2.h"
#include <algorithm>
namespace CPhysics
{
	struct Segment
	{
		Vector2 start;
		Vector2 end;

		Vector2 getClosestPoint(Vector2 point) const 
		{
			float t = Vector2::Dot(point - start, end - start) / Vector2::Dot(end - start, end - start);
			t = std::clamp(t, 0.0f, 1.0f);

			return start + (end - start) * t;
		}

		Vector2 getEdgeNormal() const 
		{

			Vector2 edge = end - start;
			return Vector2(-edge.y, edge.x).Normalized();
		}
	};
}