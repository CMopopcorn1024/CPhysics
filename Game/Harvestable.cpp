#include "Harvestable.h"

Harvestable::Harvestable(Item harvestItem, CPh::PhysicsObject* physicsObject, Texture2D texture, float scale, float rotation) : item(harvestItem), physicsObject(physicsObject), ImageObject(texture,scale,rotation)
{
}

void Harvestable::draw()
{
	CPh::Vector2 position = physicsObject->getPosition();
	ImageObject::draw(position.x, position.y);
}