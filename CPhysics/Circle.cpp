#include "Circle.h"

namespace CPhysics 
{

    Circle::Circle() : position(0, 0), radius(1) {}
    Circle::Circle(float x, float y, float radius) : position(x, y), radius(radius) {}
    Circle::Circle(Vector2 pos, float radius) : position(pos), radius(radius) {}
    

}