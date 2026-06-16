#include <iostream>
#include <raylib.h>

#include "Player.h"


#include "PhysicsObject.h"
#include "DeltaTime.h"
#include "ObjectCreation.h"

#include "Harvestable.h"

namespace CPh = CPhysics;

int main()
{
	const char* objectFilePath = "Objects.json";
    //CPhysicsObjectCreation::ObjectCreator::AddObject(objectFilePath,"Rock.png", "Basic Rock");
    //std::abort();
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Multi World Farmer");


    SetTargetFPS(60);
    CPh::DeltaTime deltaTime;


	Player player = Player(CPhysicsObjectCreation::ObjectCreator::LoadObjects(objectFilePath, "Player"), 0.5f, 0, 55.0f);

	Item basicRockItem = Item("Rock", LoadTexture("Rock.png"), 0.5f, 0);
    Harvestable basicRock = Harvestable(CPhysicsObjectCreation::ObjectCreator::LoadObjects(objectFilePath, "Basic Rock"), basicRockItem, 1, 0);

    Camera2D camera = { 0 };

    camera.target = {0, 0};
    camera.offset = { 400, 300 };
    camera.zoom = 1.0f;
    camera.rotation = 0;


    // Main game loop
    float dt = 0;

    //Load test Rock Harvestable 

    

    while (!WindowShouldClose()) 
    {
        // Update
		dt = deltaTime.getDeltaTime();
        player.update(dt);



            //Update Final
		    CPh::PhysicsObject::update(dt);


			
			CPh::Vector2 camTarget = CPh::Vector2(camera.target.x, camera.target.y);
            float t = std::clamp(4.0f * dt, 0.0f, 1.0f);
            camTarget = CPh::Vector2::Lerp(camTarget, player.getPosition(), t);
			camera.target = {camTarget.x, camTarget.y};
        
        // Draw
        BeginDrawing();

        ClearBackground(DARKBROWN);

        //Effected by camera
        BeginMode2D(camera);
        
       
        

        player.draw();
		basicRock.draw();
        
        
        EndMode2D();


		EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
