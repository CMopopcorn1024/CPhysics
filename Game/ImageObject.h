#pragma once
#include "raylib.h"
class ImageObject
{
public:
	ImageObject(Texture2D texture,float scale, float rotation);

	virtual void draw(int x, int y);
	virtual void draw() {};
private:
	float rotation, scale;
	Texture2D texture;
};

