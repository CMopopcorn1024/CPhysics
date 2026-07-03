#include "BuildMap.h"
#include "Electronic.h"


BuildMap::BuildMap(int cellSize) : cellSize(cellSize) {}

bool BuildMap::addElectronic(int x, int y, Electronic* electronic)
{
	std::pair<int, int> key = std::make_pair(x, y);
	if (electronicsMap.find(key) != electronicsMap.end())
	{
		return false; 
	}
	electronicsMap[key] = electronic;
	Electronic* nearElectronic = getElectronic(x+1, y);
	if (nearElectronic != nullptr)
	{
		nearElectronic->connectionMapUpdate(electronic);		
		electronic->connectionMapUpdate(nearElectronic);

	}

	if ((nearElectronic = getElectronic(x - 1, y)) != nullptr)
	{
		nearElectronic->connectionMapUpdate(electronic);
		electronic->connectionMapUpdate(nearElectronic);


	}

	if ((nearElectronic = getElectronic(x, y + 1)) != nullptr) 
	{
		nearElectronic->connectionMapUpdate(electronic);
		electronic->connectionMapUpdate(nearElectronic);


	}

	if ((nearElectronic = getElectronic(x, y - 1)) != nullptr) 
	{
		nearElectronic->connectionMapUpdate(electronic);
		electronic->connectionMapUpdate(nearElectronic);

	}

	
	return true;
}

Electronic* BuildMap::getElectronic(int x, int y)
{
	std::pair<int, int> key = std::make_pair(x, y);
	auto it = electronicsMap.find(key);
	if (it != electronicsMap.end())
	{
		return it->second;
	}
	return nullptr;
}

void BuildMap::draw() 
{
	for (const auto& entry: electronicsMap)
	{
		entry.second->draw();
	}
}