#pragma once
#include "Item.h"
#include "ImageObject.h"
#include "Object.h"

#include <raylib.h>

namespace CPh = CPhysics;

class Harvestable : public ImageObject, public CPhysics::Object
{
public:
	Harvestable(json data, Item harvestItem, float scale, float rotation);
	void draw() override;
private: 
	Item item;
};

