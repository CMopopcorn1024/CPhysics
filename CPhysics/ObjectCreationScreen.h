#pragma once
#include "Object.h"

#include <iostream>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


CPhysics::objectData newObject(const char* Path, const char* id)
{
    std::filesystem::path path(Path);

    std::ifstream inFile(path);


    if (!inFile)
    {
        std::cerr("Can Load File");
        std::abort();
    }

    json data;

    inFile >> data;

    inFile.close();

    CPhysics::objectData objData; 
    
    objData.id = data["id"];
    objData.mass = data["mass"];
    objData.y = data["y"];
    objData.x = data["x"];
    objData.isStatic = data["isStatic"];
    objData.bounciness = data["bounciness"];
    objData.imagePath = data["imagePath"];
    
    
    for (json rect: data["CollisionRectangles"])
    {
        objData.colRects.push_back(CPhysics::Rectangle(rect["x"],rect["y"],rect["width"],rect["height"],rect["rotation"]));
    }

    for (json rect: data["CollisionCircles"])
    {
        objData.colCircles.push_back(CPhysics::Circle(rect["x"],rect["y"],rect["radius"]));
    }


    return objData;
    
}
