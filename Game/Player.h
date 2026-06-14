#pragma once

#include "raylib.h"
#include "ImageObject.h"

//CPhysics
#include "Object.h"
namespace CPh = CPhysics;




class Player : public CPhysics::Object, public ImageObject
{
public:
	Player(json data,  float scale, float rotation, float speed);

	void draw() override
	{
		ImageObject::draw(position.x,position.y);
	}

	
	void update(float dt);

private:
	float speed;
	void checkInput(float dt);
	
};