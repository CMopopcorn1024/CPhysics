#include "Harvestable.h"

Harvestable::Harvestable(json data, Item harvestItem,  float scale, float rotation) : CPh::Object(data), item(harvestItem),  ImageObject(LoadTexture(data["ImagePath"].get<std::string>().c_str()),scale,rotation)
{
}

void Harvestable::draw()
{
	ImageObject::draw(position.x - texture.width * scale / 2, position.y - texture.height * scale / 2);
	/*for (CPh::Rectangle* rect : rects)
	{
		DrawRectangle(rect->topLeft.x, rect->topLeft.y, rect->bottomRight.x - rect->topLeft.x, rect->bottomRight.y - rect->topLeft.y, RED);
	}*/
}