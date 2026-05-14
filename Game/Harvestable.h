#pragma once
#include "Item.h"
#include "ImageObject.h"
#include "PhysicsObject.h"

#include <raylib.h>

namespace CPh = CPhysics;

class Harvestable : public ImageObject
{
public:
	Harvestable(Item harvestItem, CPh::PhysicsObject* physicsObject, Texture2D texture, float scale, float rotation);
	void draw() override;
private: 
	Item item;
	CPh::PhysicsObject* physicsObject;
};

