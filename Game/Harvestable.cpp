#include "Harvestable.h"

Harvestable::Harvestable(json data, Item harvestItem,  float scale, float rotation) : CPh::Object(data), item(harvestItem), physicsObject(physicsObject), ImageObject(LoadTexture(data["ImagePath"].get<std::string>().c_str()),scale,rotation)
{
}

void Harvestable::draw()
{
	ImageObject::draw(position.x - texture.width * scale / 2, position.y - texture.height * scale / 2);\
	for (CPh::Rectangle* rect : rects)
	{
		DrawRectangle(rect->getPosition().x - texture.width * scale / 2, rect->getPosition().y - texture.height * scale / 2, rect->getSize().x, rect->getSize().y, RED);
	}
}