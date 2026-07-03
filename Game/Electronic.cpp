#include "Electronic.h"


Electronic::Electronic(json data, float scale, float rotation, int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate, float operatingPower, std::vector<Electronic*> connectedElectronics)
	: CPh::Object(data), ImageObject(LoadTexture(data["ImagePath"].get<std::string>().c_str()), scale, rotation), LocalX(LocalX), LocalY(LocalY), map(map), powerStorageCapacity(powerStorageCapacity), powerFlowRate(powerFlowRate), operatingPower(operatingPower)
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

void Electronic::connectionMapUpdate(Electronic* updatedElectronic)
{
	int dx = updatedElectronic->getLocalX() - LocalX;
	int dy = updatedElectronic->getLocalY() - LocalY;
	connectionDirections.push_back(std::make_pair(dx, dy));
}

void Electronic::draw() 
{
	ImageObject::draw(position.x - texture.width * scale / 2, position.y - texture.height * scale / 2);
}