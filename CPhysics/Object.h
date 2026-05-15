#pragma once 
#include "PhysicsObject.h"

#include <iostream>
#include <vector>

#include <string>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace CPhysics
{
    class Object : protected PhysicsObject
    {
    public: 
        Object(PhysicsObjectProperties objProp, std::vector<Rectangle*> colRects, std::vector<Circle*> colCircles);
        
        Vector2 getPosition() {return position;}
        Vector2 getVelocity() {return velocity;}

    protected:
        static Object LoadPhysicsObject(int id);

    private:
        
        
      


    };
}

struct objectData
{
    std::string id;
    float mass;
    float x;
    float y;
    bool isStatic;
    float bounciness;
    std::string imagePath;
    std::vector<CPhysics::Rectangle*> colRects;
    std::vector<CPhysics::Circle*> colCircles;
};

void AddObject(std::string filePath, objectData objData)
{
    std::filesystem::path path(filePath);

    std::ofstream outFile(path);

    if (!outFile)
    {
        CreatFile(path);
    }

    json data;
    data["id"] = objData.id;
    data["mass"] = objData.mass;
    data["x"] = objData.x;
    data["y"] = objData.y;
    data["isStatic"] = objData.isStatic;
    data["bounciness"] = objData.bounciness;
    data["ImagePath"] = objData.imagePath;
    

    json rectData = json::array(); 
    json circleData = json::array();

    for (CPhysics::Rectangle* rect : objData.colRects)
    {
        CPhysics::Vector2 pos = rect->getPosition();
        CPhysics::Vector2 size = rect->getSize();
        rectData.push_back
        ({
            {"x" , pos.x},
            {"y", pos.y},
            {"width", size.x},
            {"height", size.y},
            {"rotation", rect->rotation}

        });
    }

    for (CPhysics::Circle* circle : objData.colCircles)
    {
        rectData.push_back
        ({
            {"x" , circle->position.x},
            {"y", circle->position.y},
            {"radius", circle->radius}

        });
    }

    data["CollisionCircles"] = circleData;
    data["CollisionRectangles"] = rectData;

    outFile << data.dump(4);
    outFile.close();
}


void CreatFile(const std::filesystem::path path)
{
    std::filesystem::create_directories(path.parent_path());
    json j;

    std::ofstream outFile(path);

    if (!outFile)
    {
        std::cerr << "failed to create file" << std::endl;
        std::abort();
    }

    outFile << j.dump(4);

    outFile.close();
}



json LoadObjects(std::string filePath, std::string id)
{
    std::filesystem::path path(filePath);

    std::ifstream inFile(path);

    if (!inFile)
    {
        CreatFile(path);
    }

    json data;

    inFile >> data;

    inFile.close();

    for (const json& obj: data)
    {
        if (obj["id"] == id)
        {
            return obj;
        }
    }


}