#include "Object.h"



namespace CPhysics
{

    Object::Object(objectData objProp) : PhysicsObject(convertToPhysicsProp(objProp), objProp.colRects, objProp.colCircles), properties(objProp)
    {
		position = Vector2(objProp.x, objProp.y);
    }

    Object::Object(json objData) : Object(convertToObjectData(objData))
    {}

    





}

