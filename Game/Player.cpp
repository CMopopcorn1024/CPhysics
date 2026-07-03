#include "Player.h"

Player::Player(json data,  float scale, float rotation, float speed) : CPh::Object(data), ImageObject(LoadTexture(data["ImagePath"].get<std::string>().c_str()), scale, rotation), speed(speed)
{}

void Player::update(float dt)
{
	checkInput(dt);
}




void Player::checkInput(float dt) 
{
	CPh::Vector2 changeVel(0, 0);
	if (IsKeyDown(KEY_W)) changeVel.y -= 1;
	if (IsKeyDown(KEY_S)) changeVel.y += 1;
	if (IsKeyDown(KEY_A)) changeVel.x -= 1;
	if (IsKeyDown(KEY_D)) changeVel.x += 1;
	changeVel = changeVel.Normalized() * speed;
	velocity += changeVel * 100 * dt;
}


void Player::draw()
{
	ImageObject::draw(position.x - texture.width * scale / 2, position.y - texture.height * scale / 2);
	/*for (CPh::Rectangle* rect : rects)
	{
		DrawRectangle(rect->topLeft.x, rect->topLeft.y, rect->bottomRight.x - rect->topLeft.x, rect->bottomRight.y - rect->topLeft.y, RED);
	}*/
}