#include "Wire.h"
#include <iostream>

Wire::Wire(int LocalX, int LocalY, BuildMap* map, float powerStorageCapacity, float powerFlowRate)
	: Electronic( 1.0f, 0.0f, LocalX, LocalY, map, powerStorageCapacity, powerFlowRate, 0.0f,std::vector<Electronic*>())
{
	
}

void Wire::connectionElectronicUpdate()
{
	std::cout << "\n\nUpdating Wire at (" << LocalX << ", " << LocalY << ")" << std::endl;
	for (const auto& dir : connectionDirections)
	{
		std::cout << "Connected to direction: (" << dir.first << ", " << dir.second << ")" << std::endl;
	}
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
		std::pair<int,int> dir1 = connectionDirections.at(0);
		std::pair<int,int> dir2 = connectionDirections.at(1);
		int dx = dir1.first - dir2.first;
		int dy = dir1.second - dir2.second;

		if (dx != 0 && dy != 0)
		{
			texture = LoadTexture("Assets/Technology/Wires/2TurnWire.png");
		
			if ( (dir1.first == -1 || dir2.first == -1) && (dir2.first == 1 || dir2.second == 1)) rotation = 0;
			else if ((dir1.first == 1 || dir2.first == 1) && (dir2.first == 1 || dir2.second == 1)) rotation = 270.0f;
			else if ((dir2.first == 1 || dir2.second == 1) && (dir2.first == -1 || dir2.second == -1)) rotation = 180.0f;
			else if ((dir2.first == -1 || dir2.second == -1) && (dir2.first == -1 || dir2.second == -1)) rotation = 90.0f;
		}

		else 
		{
			texture = LoadTexture("Assets/Technology/Wires/2StraightWire.png");
			if (dy != 0) rotation = 90.0f;
			else rotation = 0;
		}
	}

	if (numConnections == 3)
	{
		texture = LoadTexture("Assets/Technology/Wires/3Wire.png");
		if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(0, -1)) == connectionDirections.end()) rotation = 0;
		else if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(1, 0)) == connectionDirections.end()) rotation = 90.0f;
		else if (std::find(connectionDirections.begin(), connectionDirections.end(), std::make_pair(0, 1)) == connectionDirections.end()) rotation = 180.0f;
		else rotation = 270.0f;


	}
	
	if (numConnections == 4) texture = LoadTexture("Assets/Technology/Wires/4Wire.png");
	ImageObject::makeSize(50);
}