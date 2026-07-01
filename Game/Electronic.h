#pragma once

#include "ImageObject.h"
#include "Object.h"
#include <vector>
namespace CPh = CPhysics;

class Electronic : public CPhysics::Object , public ImageObject
{
public:
	Electronic(json data, float scale, float rotation, float powerStorageCapacity, float powerFlowRate, float operatingPower, std::vector<Electronic*> connectedElectronics);

	float AddPower(float delta);
	void sendPower(float dt);
protected:
	float powerStorageCapacity;
	float powerFlowRate;
	float operatingPower;

	float currentPowerStorage = 0.0f;
	std::vector<Electronic*> connectedElectronics;


};

