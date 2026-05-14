#include "ImageObject.h"


ImageObject::ImageObject(Texture2D texture, float scale, float rotation) : texture(texture), scale(scale), rotation(rotation)
{}

void ImageObject::draw(int x, int y)
{
	DrawTextureEx(texture, (Vector2){x,y}, rotation, scale, WHITE);
}