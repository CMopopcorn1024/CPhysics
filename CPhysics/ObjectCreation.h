#pragma once
#include "Object.h"

#include "raylib.h"

#include <iostream>
#include <vector>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cmath>


using json = nlohmann::json;

namespace CPhysicsObjectCreation
{
    class ObjectCreator
    {
    private:
        static json makeRects(std::string imPath);


        static void CreatFile(const std::filesystem::path path);

		static bool duplicateId(const std::filesystem::path path, std::string id);

    public:
        static void AddObject(std::string filePath, std::string imgPath, std::string id);

        static json LoadObjects(std::string filePath, std::string id);


    };
}