#pragma once

#include "ImageObject.h"
#include "Vector2.h"
#include "BuildMap.h"
#include <vector>

namespace CPh = CPhysics;

class Electronic :  public ImageObject
{
public:
	Electronic( float scale, float rotation, int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate, float operatingPower, std::vector<Electronic*> connectedElectronics);

	float AddPower(float delta);
	void sendPower(float dt);

	void connectionMapUpdate(int x, int y);
	virtual void connectionElectronicUpdate();
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
	CPh::Vector2 position;


};

