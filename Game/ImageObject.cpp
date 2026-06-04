#include "ImageObject.h"

#include <iostream>
ImageObject::ImageObject(Texture2D texture, float scale, float rotation) : texture(texture), scale(scale), rotation(rotation)
{

}

void ImageObject::draw(float x, float y)
{
	if (texture.id == 0) std::cout << "Texture not loaded correctly" << std::endl;
	DrawTextureEx(texture, {x,y}, rotation, scale, WHITE);
}