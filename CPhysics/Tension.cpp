#include "Tension.h"
#include "PhysicsObject.h"
#include <iostream>
namespace CPhysics
{
	Tension::Tension(float strength, float dp, float normalLength, PhysicsObject& objA, PhysicsObject& objB, bool duel) : strength(strength), normalLength(normalLength), objA(objA), objB(objB), damping(dp), duel(duel)
	{
        PhysicsObject::addTension(this);
    }

	void Tension::ApplyTension(float dt)
	{
		Vector2 delta = objB.getPosition() - objA.getPosition();
		float dist = delta.length();

		if (dist == 0.0f) return;

		Vector2 dir = delta / dist;

		float displacement = dist - normalLength;

		if (!duel && displacement < 0) return;

		Vector2 relVel = objB.getVelocity() - objA.getVelocity();

		Vector2 springForce = dir * (-strength * displacement);

		float velAlongDir = Vector2::Dot(relVel, dir);
		Vector2 dampingForce = dir * (velAlongDir * damping);

		Vector2 totalForce = springForce - dampingForce;

		std::cout << totalForce.x << " " << totalForce.y << std::endl;
		// apply
		if (!objA.getProp().isStatic)
			objA.changeVelocity(totalForce / -objA.getProp().mass * dt);
		if (!objB.getProp().isStatic)
			objB.changeVelocity(totalForce / objB.getProp().mass * dt);


	}
}