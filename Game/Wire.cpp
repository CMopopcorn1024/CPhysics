#include "Wire.h"


Wire::Wire(json data, float scale, int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate)
	: Electronic(data, scale, 0.0f, LocalX, LocalY, map, powerStorageCapacity, powerFlowRate, 0.0f,std::vector<Electronic*>())
{
	
}

void Wire::connectionMapUpdate(Electronic* updatedElectronic)
{
	Electronic::connectionMapUpdate(updatedElectronic);

	int numConnections = connectionDirections.size();
	if (numConnections == 0) texture = LoadTexture("Assets/Technology/Wires/0Wire.png");

	if (numConnections == 1)
	{
		texture = LoadTexture("Assets/Technology/Wires/1Wire.png");
		if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(0, -1)) != connectionDirections.end()) rotation = 90.0f;
		if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(1, 0)) != connectionDirections.end()) rotation = 180.0f;
		if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(0, 1)) != connectionDirections.end()) rotation = 270.0f;
		
	}

	if (numConnections == 2)
	{
		texture = LoadTexture("Assets/Technology/Wires/2Wire.png");
	}

	if (numConnections == 3)
	{
		texture = LoadTexture("Assets/Technology/Wires/3Wire.png");
		if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(1, 0)) == connectionDirections.end()) rotation = 90.0f;
		if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(0, 1)) == connectionDirections.end()) rotation = 180.0f;
		if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(-1, 0)) == connectionDirections.end()) rotation = 270.0f;

	}
	
	if (numConnections == 4) texture = LoadTexture("Assets/Technology/Wires/4Wire.png");
	
}