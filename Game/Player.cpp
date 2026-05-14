#include "Player.h"

Player::Player(CPh::PhysicsObject* physicsObject, float speed) : physicsObject(physicsObject), speed(speed)
{}


void Player::draw()
{
	CPh::Vector2 pos = physicsObject->getPosition();
	CPh::Vector2 size(20,20);
	DrawCircle(pos.x, pos.y, size.x , BLUE);
}

void Player::update(float dt)
{
	checkInput(dt);
}

void Player::checkInput(float dt)
{
	CPh::Vector2 velocity(0, 0);
	if (IsKeyDown(KEY_W)) velocity.y -= 1;
	if (IsKeyDown(KEY_S)) velocity.y += 1;
	if (IsKeyDown(KEY_A)) velocity.x -= 1;
	if (IsKeyDown(KEY_D)) velocity.x += 1;
	velocity = velocity.Normalized() * speed;
	physicsObject->changeVelocity(velocity * 100 * dt);
}
