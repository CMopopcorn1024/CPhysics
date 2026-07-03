#include "Electronic.h"

#include <iostream>
Electronic::Electronic( float scale, float rotation, int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate, float operatingPower, std::vector<Electronic*> connectedElectronics)
	:  ImageObject(LoadTexture("Assets/Unloaded.png"), scale, rotation), LocalX(LocalX), LocalY(LocalY), map(map), powerStorageCapacity(powerStorageCapacity), powerFlowRate(powerFlowRate), operatingPower(operatingPower)
{
	map->addElectronic(LocalX, LocalY, this);
	position = map->getPosition(LocalX, LocalY);
	ImageObject::makeSize(50);

	

}


float Electronic::AddPower(float delta)
{
	currentPowerStorage += delta;
	if (currentPowerStorage > powerStorageCapacity)
	{
		float excess = currentPowerStorage - powerStorageCapacity;
		currentPowerStorage = powerStorageCapacity;
		return excess;
	}
	return 0;

}


void Electronic::sendPower(float dt)
{
	for (Electronic* e : connectedElectronics) 
	{
		float returnPower = e->AddPower(powerFlowRate * dt);
		currentPowerStorage -= (powerFlowRate * dt) - returnPower;
	}
}

void Electronic::connectionMapUpdate(int x, int y)
{
	std::cout << LocalX << " " << LocalY << " is connected to " << x << " " << y << std::endl;
	int dx = x - LocalX;
	int dy = y - LocalY;
	std::pair<int, int> direction = std::make_pair(dx, dy);
	if (std::find(connectionDirections.begin(), connectionDirections.end(), direction) == connectionDirections.end())
	{
		connectionDirections.push_back(direction);
	}
}

void Electronic::draw() 
{
	ImageObject::draw(position.x - texture.width * scale / 2, position.y - texture.height * scale / 2);
}

void Electronic::connectionElectronicUpdate()
{
	
}