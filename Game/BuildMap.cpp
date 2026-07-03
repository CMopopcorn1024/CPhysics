#include "BuildMap.h"
#include "Electronic.h"


BuildMap::BuildMap(int cellSize) : cellSize(cellSize) {}

bool BuildMap::addElectronic(int x, int y, Electronic* electronic)
{
	std::pair<int, int> key = std::make_pair(x, y);
	newElectricPosition.push_back(key);
	if (electronicsMap.find(key) != electronicsMap.end())
	{
		return false; 
	}
	electronicsMap[key] = electronic;

	Electronic* nearElectronic = getElectronic(electronic->getLocalX() + 1, electronic->getLocalY());
	if (nearElectronic != nullptr)
	{
		nearElectronic->connectionMapUpdate(x,y);
		electronic->connectionMapUpdate(x+1,y);
	}

	if ((nearElectronic = getElectronic(electronic->getLocalX() - 1, electronic->getLocalY())) != nullptr)
	{
		nearElectronic->connectionMapUpdate(x,y);
		electronic->connectionMapUpdate(x-1,y);
	}

	

	if ((nearElectronic = getElectronic(electronic->getLocalX(), electronic->getLocalY() + 1)) != nullptr)
	{
		nearElectronic->connectionMapUpdate(x,y);
		electronic->connectionMapUpdate(x,y+1);
	}

	if ((nearElectronic = getElectronic(electronic->getLocalX(), electronic->getLocalY() - 1)) != nullptr)
	{
		nearElectronic->connectionMapUpdate(x,y);
		electronic->connectionMapUpdate(x,y-1);
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

void BuildMap::updateConnectionMaps()
{
	for (std::pair<int, int> pos : newElectricPosition)
	{
		getElectronic(pos.first, pos.second)->connectionElectronicUpdate();
	}
	newElectricPosition.clear();
}