#pragma once
#include "Vector2.h"

#include <cmath>
#include <vector>
namespace CPhysics
{
	class PhysicsObject;
	class Tension
	{
	public:
		Tension(float strength, float dp, float normalLength, PhysicsObject& objA, PhysicsObject& objB, bool duel = false);
		void ApplyTension(float dt);
	private:
		float strength;
		float normalLength;
		float damping;
		PhysicsObject& objA;
		PhysicsObject& objB;
		bool duel;
	};
}
