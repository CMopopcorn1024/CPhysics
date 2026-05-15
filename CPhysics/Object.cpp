#include "Object.h"



namespace CPhysics
{
    Object::Object(PhysicsObjectProperties objProp, std::vector<Rectangle*> colRects, std::vector<Circle*> colCircles) : PhysicsObject(objProp,colRects,colCircles)
    {}

    Object Object::LoadPhysicsObject(int id)
    {
        
    }


}

