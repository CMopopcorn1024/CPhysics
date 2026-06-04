#include "Player.h"


Player::Player(json data,  float scale, float rotation) : CPh::Object(data), ImageObject(LoadTexture(data["ImagePath"].get<std::string>().c_str()), scale, rotation)
{}