#include "ImageObject.h"

#include <iostream>
ImageObject::ImageObject(Texture2D texture, float scale, float rotation) : texture(texture), scale(scale), rotation(rotation)
{

}

void ImageObject::draw(float x, float y)
{
	if (texture.id == 0) std::cout << "Texture not loaded correctly" << std::endl;
	
	Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
	Rectangle dest = { x, y, (float)texture.width*scale, (float)texture.height *scale};
	Vector2 origin = { texture.width / 2.0f*scale, texture.height / 2.0f*scale };
	

	DrawTexturePro(texture, source,dest,origin, rotation,  WHITE);
}

void ImageObject::makeSize(float size)
{
	float width = static_cast<float>(texture.width);
	float height = static_cast<float>(texture.height);
	float maxDimension = std::max(width, height);
	scale = size / maxDimension;
}