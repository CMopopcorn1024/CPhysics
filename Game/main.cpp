#include <iostream>
#include <raylib.h>

#include "Player.h"


#include "PhysicsObject.h"
#include "DeltaTime.h"

#include "Harvestable.h"

namespace CPh = CPhysics;

int main()
{
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Multi World Farmer");


    SetTargetFPS(60);
    CPh::DeltaTime deltaTime;


    //New way to load object type combining Object.h and ColliderSave.h into one object using a graphical interfase to create the object
    
        /*Player player(&playerPhysicsObject, 35.0f);

        Texture2D texture  = LoadTexture("Game/Rock.png");
    
        Item rockItem("Rock", texture, 1,0);
        CPh::PhysicsObject rockPhysicsObject = CPh::loadObject("Rock");
        
        Harvestable Rock(rockItem, &rockPhysicsObject,texture,1,0);*/

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
        //player.update(dt);



            //Update Final
		    CPh::PhysicsObject::update(dt);


			
			CPh::Vector2 camTargetCPh = CPh::Vector2(camera.target.x, camera.target.y);
            //camTargetCPh = CPh::Vector2::Lerp(camTargetCPh, player.getPosition(), 4.0f * dt);
			//camera.target = {camTargetCPh.x, camTargetCPh.y};
           
        // Draw
        BeginDrawing();

        ClearBackground(DARKBROWN);

        //Effected by camera
        BeginMode2D(camera);
        
       
        

        //player.draw();
        //Rock.draw();
        
        EndMode2D();


		EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
