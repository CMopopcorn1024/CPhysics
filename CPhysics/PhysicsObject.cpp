#include "PhysicsObject.h"

namespace CPhysics
{
	PhysicsObject::PhysicsObject(PhysicsObjectProperties objProp, Rectangle colRect) : prop(objProp), colRect(colRect) 
	{
		prop.isRect = true;
	}

	PhysicsObject::PhysicsObject(PhysicsObjectProperties objProp, Circle colCircle) : prop(objProp), colCircle(colCircle)
	{
		prop.isCircle = true;
	}
}