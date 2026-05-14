#include "Item.h"


Item::Item(std::string name, Texture2D texture, float scale, float rotation) : name(name), ImageObject(texture, scale, rotation) {}