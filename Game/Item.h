#pragma once
#include <String>
#include "raylib.h"

#include "ImageObject.h"

class Item : public ImageObject
{
public: 
	Item(std::string name, Texture2D texture, float scale, float rotation);
private:
	std::string name;
};

