#include "Wire.h"


Wire::Wire(json data, float scale, float powerStorageCapacity, float powerFlowRate)
	: Electronic(data, scale, 0.0f, powerStorageCapacity, powerFlowRate, 0.0f)
{}