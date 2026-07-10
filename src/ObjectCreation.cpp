#include "ObjectCreation.h"




namespace CPhysicsObjectCreation
{

    void ObjectCreator::AddObject(std::string filePath, std::string imgPath, std::string id)
    {
        std::filesystem::path path(filePath);

       
        if (!std::filesystem::exists(path))
        {
            
            CreatFile(path);
			std::cerr << "Created object json file ... rerun your program" << std::endl;
            std::abort();
        }



        if (duplicateId(path, id)) 
        {
            
			std::cerr << "Object with this ID already exists" << std::endl;
            std::abort();
        }
        else 
        {
            std::ifstream inFile(path);
            
            json otherData; 

			inFile >> otherData;
			inFile.close();

            json data;
            data["id"] = id;
            data["mass"] = 100;
            data["x"] = 0;
            data["y"] = 0;
            data["isStatic"] = false;
            data["bounciness"] = 0.5;
            data["drag"] = 0.1;
            data["ImagePath"] = imgPath;






           

            json colData = makeRects(imgPath);
            
            data["CollisionRectangles"] = colData["CollisionRectangles"];
            data["CollisionCircles"] = colData["CollisionCircles"];


			otherData.push_back(data);

            std::ofstream outFile(path);

            outFile << otherData.dump(4);
            outFile.close();

        }
    }

    void ObjectCreator::CreatFile(const std::filesystem::path path)
    {
        
		std::cout << "Creating file: " << path << std::endl;

        auto parent = path.parent_path();

        if (!parent.empty()) std::filesystem::create_directories(path.parent_path());
        json j = json::array();

        std::ofstream outFile(path);

        if (!std::filesystem::exists(path))
        {
            std::cerr << "failed to create file" << std::endl;
            std::abort();
        }

        outFile << j.dump(4);

        outFile.close();
    }

    bool ObjectCreator::duplicateId(const std::filesystem::path path, const std::string id)
    {
        std::ifstream inFile(path);
        if (!std::filesystem::exists(path))
        {
            return false;
        }

        json data;
        try
        {
            inFile >> data;
            inFile.close();
        }
        catch (...)
        {
            inFile.close();
            return false;
        }
        for (const json& obj : data)
        {
            if (obj["id"] == id)
            {
                return true;
            }
        }
        return false;
    }

    json ObjectCreator::LoadObjects(std::string filePath, std::string id)
    {
        std::filesystem::path path(filePath);


        if (!std::filesystem::exists(path))
        {
            CreatFile(path);
            std::cerr << "Created object json file ... rerun your program" << std::endl;
            std::abort();
        }

        std::ifstream inFile(path);

        json data;

        inFile >> data;

        inFile.close();

        for (const json& obj : data)
        {
            if (obj["id"] == id)
            {
                return obj;
            }
        }

        std::cerr << "Cant find object with this ID: " << id << std::endl;
        std::abort();
        return data;


    }


    json ObjectCreator::makeRects(std::string imgpath)
    {
        
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Multi World Farmer");

    SetTargetFPS(60);
    if (!FileExists(imgpath.c_str())) { std::cout << " cant load texture "; std::abort(); }

    Texture texture = LoadTexture(imgpath.c_str());

    if (texture.id == 0) { std::cout << " cant load texture "; std::abort(); }

    float scale = std::min((float)screenWidth/texture.width, (float)screenHeight/texture.height);

    std::vector<Rectangle> rects;

    Vector2 rectStartPos = { -1, -1 };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKBROWN);

		DrawTextureEx(texture, { 0, 0 }, 0, scale, WHITE);



        

        if (rectStartPos.x != -1)
        {
            Vector2 currentMousePos = GetMousePosition();
            float xL = std::min(rectStartPos.x, currentMousePos.x);
            float xR = std::max(rectStartPos.x, currentMousePos.x);

            float yL = std::min(rectStartPos.y, currentMousePos.y);
            float yR = std::max(rectStartPos.y, currentMousePos.y);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                rects.push_back({ xL, yL, xR - xL, yR - yL });
                rectStartPos = { -1, -1 };
            }
            else DrawRectangleLines(xL, yL, xR - xL, yR - yL, RED);

        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            rectStartPos = GetMousePosition();

        }

		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			if (rectStartPos.x != -1) rectStartPos = { -1, -1 };
            else 
            {
				Rectangle mouseRect = { GetMousePosition().x, GetMousePosition().y, 1, 1 };
                for (int i = 0; i < rects.size(); i++) 
                {
                    if (CheckCollisionRecs(mouseRect, rects[i]))
                    {
                        rects.erase(rects.begin() + i);
                        break;
                    }
                }
            }
		}

        for (const Rectangle& rect : rects)
        {
			DrawRectangleRec(rect, Fade(RED, 0.5f));
        }



        EndDrawing();
    }

    CloseWindow();

	json objectData = json::object();

	json rectData = json::array();
	json circleData = json::array();

    for (Rectangle& rect : rects) 
    {
		rectData.push_back({ {"x", rect.x/scale}, {"y", rect.y/scale}, {"width", rect.width/scale}, {"height", rect.height/scale}, {"rotation", 0} });
    }

    objectData["CollisionRectangles"] = rectData;
    objectData["CollisionCircles"] = circleData;
    
    return objectData;

    }


    

}