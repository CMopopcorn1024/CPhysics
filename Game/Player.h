#pragma once
#include "PhysicsObject.h"
#include "Object.h"
#include <raylib.h>

namespace CPh = CPhysics;

class Player : private CPh::Object
{

public:
	Player(float speed);

	void draw();

	void update(float dt);
	
	CPh::Vector2 getPosition() const { return physicsObject->getPosition(); }
	CPh::PhysicsObject* getPhysicsObject() {return physicsObject;}
private:
	int speed;
	CPh::PhysicsObject* physicsObject;
	void checkInput(float dt);
};

