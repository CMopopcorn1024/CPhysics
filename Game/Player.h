#pragma once

#include "raylib.h"
#include "ImageObject.h"

//CPhysics
#include "Object.h"
namespace CPh = CPhysics;




class Player : public CPhysics::Object, public ImageObject
{
public:
	Player(json data,  float scale, float rotation);

	void draw() override
	{
		ImageObject::draw(position.x,position.y);
		DrawCircle(position.x, position.y, 5, RED);
	}

	
};