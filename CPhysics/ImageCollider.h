#pragma once

#include "raylib.h"
#include "Rectangle.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ColliderTool
{
    static const std::string PATH = "colliders.json";

    static json loadCollidersFile()
    {
        if (!std::filesystem::exists(PATH))
        {
            json j;
            j["colliders"] = json::array();

            std::ofstream out(PATH);
            out << j.dump(4);
            return j;
        }

        std::ifstream in(PATH);

        if (!in.is_open() ||
            in.peek() == std::ifstream::traits_type::eof())
        {
            std::cerr << "[colliders.json] Missing/empty → repairing\n";

            json j;
            j["colliders"] = json::array();

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
            std::cerr << "[colliders.json] Corrupted → repairing: "
                      << e.what() << "\n";

            j["colliders"] = json::array();

            std::ofstream out(PATH);
            out << j.dump(4);
        }

        if (!j.contains("colliders") || !j["colliders"].is_array())
            j["colliders"] = json::array();

        return j;
    }

    static json getColliderByKey(const json& j, const std::string& key)
    {
        if (!j.contains("colliders"))
            return json();

        for (const auto& c : j["colliders"])
        {
            if (c.value("key", "") == key)
                return c;
        }

        return json();
    }

    static void saveCollider(const char* imagePath,
                             const char* imageName,
                             const std::vector<CPhysics::Rectangle>& rects)
    {
        json j = loadCollidersFile();

        json collider;
        collider["key"] = imageName;
        collider["imagePath"] = imagePath;
        collider["rectangles"] = json::array();

        for (const auto& r : rects)
        {
            collider["rectangles"].push_back({
                {"x", r.topLeft.x},
                {"y", r.topLeft.y},
                {"w", r.getSize().x},
                {"h", r.getSize().y}
            });
        }

        j["colliders"].push_back(collider);

        std::ofstream out(PATH);
        out << j.dump(4);
    }

    static std::vector<CPhysics::Rectangle> loadColliders(const char* imageName)
    {
        json j = loadCollidersFile();

        json collider = getColliderByKey(j, imageName);

        std::vector<CPhysics::Rectangle> result;

        if (collider.is_null())
            return result;

        for (const auto& r : collider["rectangles"])
        {
            result.push_back(CPhysics::Rectangle{
                r.value("x", 0.0f),
                r.value("y", 0.0f),
                r.value("w", 0.0f),
                r.value("h", 0.0f)
            });
        }

        return result;
    }
}