#pragma once
#include "Electronic.h"

class Wire : public Electronic
{
public:
	Wire(int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate);
	void connectionElectronicUpdate() override;
	
};

