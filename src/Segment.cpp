#include <CPhysics/Segment.h>
#include <algorithm>

namespace CPhysics
{

     Vector2 Segment::getClosestPoint(Vector2 point)  const 
    {
        float t = Vector2::Dot(point - start, end - start) / Vector2::Dot(end - start, end - start);
        t = std::clamp(t, 0.0f, 1.0f);

        return start + (end - start) * t;
    }

    Vector2 Segment::getEdgeNormal() const 
    {

        Vector2 edge = end - start;
        return Vector2(-edge.y, edge.x).Normalized();
    }

}