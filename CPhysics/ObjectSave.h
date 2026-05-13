#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "PhysicsObject.h"
#include "CollisionObject.h"

using json = nlohmann::json;

namespace CPhysics
{
    static const std::string PATH = "objects.json";

    static json loadObjectsFile()
    {
        // Create file if missing OR empty
        if (!std::filesystem::exists(PATH))
        {
            json j;
            j["objects"] = json::array();

            std::ofstream out(PATH);
            out << j.dump(4);
            return j;
        }

        std::ifstream in(PATH);

        // Empty file protection
        if (!in.is_open() ||
            in.peek() == std::ifstream::traits_type::eof())
        {
            std::cerr << "[objects.json] Missing or empty → repairing\n";

            json j;
            j["objects"] = json::array();

            std::ofstream out(PATH);
            out << j.dump(4);
            return j;
        }

        json j;

        try
        {
            in >> j;
        }
        catch (const json::parse_error& e)
        {
            std::cerr << "[objects.json] Corrupted JSON → repairing: "
                      << e.what() << "\n";

            j["objects"] = json::array();

            std::ofstream out(PATH);
            out << j.dump(4);
        }

        if (!j.contains("objects") || !j["objects"].is_array())
            j["objects"] = json::array();

        return j;
    }

    void newObject(const char* name, bool isRect, bool isStatic)
    {
        json j = loadObjectsFile();

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
        else
        {
            properties["isStatic"] = true;
        }

        object["properties"] = properties;
        j["objects"].push_back(object);

        std::ofstream out(PATH);
        out << j.dump(4);
    }

    PhysicsObject loadObject(const char* name)
    {
        PhysicsObjectProperties props{};
        CollisionObject* colObj = nullptr;

        json j = loadObjectsFile();

        for (const auto& obj : j["objects"])
        {
            if (obj.value("key", "") != name)
                continue;

            const json& p = obj["properties"];

            int x = p.value("x", 0);
            int y = p.value("y", 0);

            if (p.contains("mass") && p.contains("bounce") && p.contains("drag"))
            {
                props.mass = p.value("mass", 1.0f);
                props.bounciness = p.value("bounce", 0.8f);
                props.drag = p.value("drag", 2.0f);
            }
            else
            {
                props.isStatic = true;
            }

            if (p.contains("width") && p.contains("height"))
            {
                float w = p.value("width", 1.0f);
                float h = p.value("height", 1.0f);

                colObj = new CollisionObject(
                    new Rectangle{ (float)x, (float)y, w, h }
                );
            }
            else if (p.contains("radius"))
            {
                float r = p.value("radius", 1.0f);

                colObj = new CollisionObject(
                    new Circle{ (float)x, (float)y, r }
                );
            }

            break;
        }

        return PhysicsObject(props, colObj);
    }
}