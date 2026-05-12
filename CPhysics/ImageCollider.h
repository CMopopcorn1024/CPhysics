#pragma once
#include "raylib.h"

#include <iostream>
#include "Rectangle.h"
#include <vector>
#include <unordered_map>
#include <cmath>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace ColliderTool
{
    static struct colliderCreator
    {
        static void getImageCollider(const char* imagePath,const char* imageName)
        {



            InitWindow(1000.0f, 1000.0f, "Basic Raylib Window");


            Texture2D texture = LoadTexture(imagePath);

            if (texture.id == 0)
            {
                std::cout << "not valid image" << std::endl;
                return;
            }

            float scale = 1000.0f / texture.width;

            SetWindowSize(1000.0f, texture.height * scale);

            SetTargetFPS(60);

            // Main game loop
            Rectangle* temp = nullptr;
            Vector2 tempStartPos;
            std::vector<Rectangle> rectangles;


            while (!WindowShouldClose())    // Detect window close button or ESC key
            {

                Vector2 mousePos = GetMousePosition();

                Rectangle mouseRect = { mousePos.x, mousePos.y, 1, 1 };

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    tempStartPos = mousePos;
                    temp = new Rectangle();
                    temp->x = mousePos.x;
                    temp->y = mousePos.y;
                }

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                {

                    temp->x = std::min(tempStartPos.x, mousePos.x);
                    temp->y = std::min(tempStartPos.y, mousePos.y);

                    temp->width = std::abs(mousePos.x - tempStartPos.x);
                    temp->height = std::abs(mousePos.y - tempStartPos.y);

                }

                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                {
                    rectangles.push_back(*temp);
                    temp = nullptr;
                }


                else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
                {
                    for (int i = 0; i < rectangles.size(); i++)
                    {
                        if (CheckCollisionRecs(mouseRect, rectangles.at(i)))
                        {
                            rectangles.erase(rectangles.begin() + i);
                            break;
                        }

                    }
                }


                BeginDrawing();

                ClearBackground(BLACK);

                DrawTextureEx(texture, Vector2(0, 0), 0, scale, WHITE);

                for (const Rectangle& rect : rectangles)
                {
                    DrawRectangleRec(rect, RED);
                }

                if (temp != nullptr) DrawRectangleRec(*temp, BLUE);

                EndDrawing();
            }

            CloseWindow();
            saveCollider(imagePath,imageName,rectangles);

        }
        static std::vector<CPhysics::Rectangle> loadColliders(const char* imageName)
        {
            std::ifstream file("colliders.json");
            json j;
            file >> j;
            
            json collider = getColliderByKey(j, imageName);
            std::vector<CPhysics::Rectangle> rectangles;
            if (!collider.is_null())
            {
                
                for (const auto& r : collider["rectangles"])
                {
                    float x = r["x"];
                    float y = r["y"];
                    float w = r["w"];
                    float h = r["h"];

                    rectangles.push_back(CPhysics::Rectangle{ x,y,w,h });
                }
            }
			return rectangles;

        }

    private:
        static void saveCollider(const char* imagePath,const char* imageName,const std::vector<Rectangle>& rectangles) 
        {
            const std::string path = "colliders.json";

            // ---- CREATE FILE IF IT DOES NOT EXIST ----
            if (!std::filesystem::exists(path))
            {
                json init;
                init["colliders"] = json::array();

                std::ofstream createFile(path);
                createFile << init.dump(4);
                createFile.close();
            }

            // ---- LOAD EXISTING FILE ----
            std::ifstream inFile(path);
            json j;
            inFile >> j;
            inFile.close();

            // ---- SAFETY CHECK ----
            if (!j.contains("colliders"))
            {
                j["colliders"] = json::array();
            }

            // ---- BUILD COLLIDER ----
            json collider;
            collider["key"] = imageName;
            collider["imagePath"] = imagePath;
            collider["rectangles"] = json::array();

            for (const auto& r : rectangles)
            {
                collider["rectangles"].push_back({
                    {"x", r.x},
                    {"y", r.y},
                    {"w", r.width},
                    {"h", r.height}
                    });
            }

            // ---- SAVE DATA ----
            j["colliders"].push_back(collider);

            std::ofstream outFile(path);
            outFile << j.dump(4);
            outFile.close();
        }
        static json getColliderByKey(const json& j, const std::string& key)
        {
            if (!j.contains("colliders")) return nullptr;

            for (const auto& collider : j["colliders"])
            {
                if (collider.contains("key") && collider["key"] == key)
                {
                    return collider; // found it
                }
            }

            return nullptr; // not found
        }
};
    
}