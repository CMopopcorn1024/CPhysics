#pragma once

#include "ImageObject.h"
#include "Object.h"
#include "BuildMap.h"
#include <vector>

namespace CPh = CPhysics;

class Electronic : public CPhysics::Object , public ImageObject
{
public:
	Electronic(json data, float scale, float rotation, int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate, float operatingPower, std::vector<Electronic*> connectedElectronics);

	float AddPower(float delta);
	void sendPower(float dt);

	virtual void connectionMapUpdate(Electronic* updatedElectronic);
	int getLocalX() { return LocalX; }
	int getLocalY() { return LocalY; }

	void draw() override;
protected:
	float powerStorageCapacity;
	float powerFlowRate;
	float operatingPower;

	float currentPowerStorage = 0.0f;
	std::vector<Electronic*> connectedElectronics;

	int LocalX;
	int LocalY;
	std::vector<std::pair<int, int>> connectionDirections;
	BuildMap* map;


};

