#include "ImageObject.h"


ImageObject::ImageObject(Texture2D texture, float scale, float rotation) : texture(texture), scale(scale), rotation(rotation)
{}

void ImageObject::draw(float x, float y)
{
	DrawTextureEx(texture, {x,y}, rotation, scale, WHITE);
}