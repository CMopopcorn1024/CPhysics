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
        static Object LoadPhysicsObject(std::string id);

    private:
        static const std::string Path = "Objects.json";
        
        
      


    };


    //Object Data Getter

    struct objectData
    {
        std::string id;
        float mass;
        float x;
        float y;
        bool isStatic;
        float bounciness;
        std::string imagePath;
        std::vector<CPhysics::Rectangle> colRects;
        std::vector<CPhysics::Circle> colCircles;
    };


    void AddObject(std::string filePath, objectData objData);

    void CreatFile(const std::filesystem::path path);

    json LoadObjects(std::string filePath, std::string id);
}