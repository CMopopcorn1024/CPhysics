#include "Electronic.h"


Electronic::Electronic(json data, float scale, float rotation, float powerStorageCapacity, float powerFlowRate, float operatingPower, std::vector<Electronic*> connectedElectronics) 
	: CPh::Object(data), ImageObject(LoadTexture(data["ImagePath"].get<std::string>().c_str()), scale, rotation), powerStorageCapacity(powerStorageCapacity), powerFlowRate(powerFlowRate), operatingPower(operatingPower)
{}


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