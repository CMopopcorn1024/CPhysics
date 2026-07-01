#pragma once
#include "Electronic.h"
class Wire : public Electronic
{
public:
	Wire(json data, float scale, float powerStorageCapacity, float powerFlowRate);
};

