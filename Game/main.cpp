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
    
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Multi World Farmer");


    SetTargetFPS(60);
    CPh::DeltaTime deltaTime;


	Player player = Player(CPhysicsObjectCreation::ObjectCreator::LoadObjects(objectFilePath, "Basic Rock"), 1.0f, 0, 200.0f);

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


			
			CPh::Vector2 camTargetCPh = CPh::Vector2(camera.target.x, camera.target.y);
            camTargetCPh = CPh::Vector2::Lerp(camTargetCPh, player.getPosition(), 4.0f * dt);
			camera.target = {camTargetCPh.x, camTargetCPh.y};
			std::cout << "Camera Target: " << player.getPosition().x << ", " << player.getPosition().y << std::endl;
           
        // Draw
        BeginDrawing();

        ClearBackground(DARKBROWN);

        //Effected by camera
        BeginMode2D(camera);
        
       
        

        player.draw();
        
        
        EndMode2D();


		EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
