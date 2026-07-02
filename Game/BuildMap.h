#pragma once
#include <unordered_map>
#include <utility>

class Electronic;

class BuildMap
{
public:
	BuildMap();
	bool addElectronic(int x, int y, Electronic* electronic);
	Electronic* getElectronic(int x, int y);
private:
	std::unordered_map<std::pair<int, int>, Electronic*> electronicsMap;
};

