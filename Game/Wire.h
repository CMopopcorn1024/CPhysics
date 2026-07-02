#pragma once
#include "Electronic.h"

class Wire : public Electronic
{
public:
	Wire(json data, float scale, int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate);
	void connectionMapUpdate(Electronic* updatedElectronic) override;
	
};

