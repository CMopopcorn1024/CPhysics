#pragma once
#include "raylib.h"
class ImageObject
{
public:
	ImageObject(Texture2D texture,float scale, float rotation);

	virtual void draw(float x, float y);
	virtual void draw() {};
	void makeSize(float size);
protected:
	float rotation, scale;
	Texture2D texture;
};

