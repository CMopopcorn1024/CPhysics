#pragma once
#include <nlohmann/json.hpp>
#include <fstream>

#include "PhysicsObject.h"
#include "CollisionObject.h"
using json = nlohmann::json;

namespace CPhysics
{
	void newObject(const char* name, bool isRect, bool isStatic) 
	{
        const std::string path = "objects.json";

        // Create file if missing
        if (!std::filesystem::exists(path))
        {
            json init;
            init["objects"] = json::array();

            std::ofstream createFile(path);
            createFile << init.dump(4);
        }

        // Load file
        std::ifstream inFile(path);
        json j;
        inFile >> j;

        if (!j.contains("objects"))
        {
            j["objects"] = json::array();
        }

        // Create object
        json object;
        object["key"] = name;

        json properties;

        properties["x"] = 0;
        properties["y"] = 0;
        properties["imageName"] = "null";

        if (isRect)
        {
            properties["width"] = 1;
            properties["height"] = 1;
        }
        else
        {
            properties["radius"] = 1;
        }

        if (!isStatic)
        {
            properties["mass"] = 1.0;
            properties["bounce"] = 0.8;
			properties["drag"] = 2.0;
        }

        object["properties"] = properties;

        // Add object
        j["objects"].push_back(object);

        // Save
        std::ofstream outFile(path);
        outFile << j.dump(4);
	}
    
    PhysicsObject loadObject(const char* name) 
    {
        PhysicsObjectProperties properties;
        CollisionObject* colObj = nullptr;


        std::ifstream inFile("objects.json");

        json j;
        inFile >> j;
        inFile.close();


        for (auto& obj : j["objects"])
        {
            if (obj["key"] == name)
            {
				json prop = obj["properties"];
                
                int x = prop["x"];
				int y = prop["y"];
                
                if (prop.contains("bounce") && prop.contains("mass") && prop.contains("drag"))
                {

                    properties.bounciness = prop["bounce"];
                    properties.mass = prop["mass"];
                    properties.drag = prop["drag"];
                }
                else 
                {
                    properties.isStatic = true;
                }



                if (prop.contains("width") && prop.contains("height"))
                {
                    int width = prop["width"];
                    int height = prop["height"];
                    colObj = new CollisionObject(new Rectangle{ (float)x,(float)y,(float)width,(float)height });
                    
                }
                else if (prop.contains("radius"))
                {
                    int radius = prop["radius"];
                    colObj = new CollisionObject(new Circle{ (float)x,(float)y,(float)radius });
                }
                break;
            }
        }

		return PhysicsObject(properties,colObj);

    }

}