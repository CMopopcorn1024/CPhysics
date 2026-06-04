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

    struct objectData
    {
        std::string id;
        float mass;
        float drag;
        float x;
        float y;
        bool isStatic;
        float bounciness;
        std::string imagePath;
        std::vector<CPhysics::Rectangle*> colRects;
        std::vector<CPhysics::Circle*> colCircles;
    };

    class Object : protected PhysicsObject
    {



    public: 
        Object(objectData objProp);

        Object(json data);
        
        Vector2 getPosition() {return position;}
        Vector2 getVelocity() {return velocity;}

    protected:
		const char* getImagePath() { return properties.imagePath.c_str(); }
    private:
        
        static PhysicsObjectProperties convertToPhysicsProp(objectData objProp)
         {
             PhysicsObjectProperties prop;
             prop.mass = objProp.mass;
             prop.drag = objProp.drag;
             prop.isStatic = objProp.isStatic;
             prop.bounciness = objProp.bounciness;
             return prop;
         }
        static objectData convertToObjectData(json data) 
        {

            objectData prop;
            prop.bounciness = data["bounciness"];
            prop.mass = data["mass"];
            prop.isStatic = data["isStatic"];
            prop.drag = data["drag"];
            prop.x = data["x"];
            prop.y = data["y"];

            std::vector<Rectangle*> colRects;
            std::vector<Circle*> colCircles;

            
            for (json rect : data["CollisionRectangles"])
            {
                colRects.push_back(new Rectangle(rect["x"], rect["y"], rect["width"], rect["height"], rect["rotation"]));
            }

            for (json circle : data["CollisionCircles"])
            {
                colCircles.push_back(new Circle(circle["x"], circle["y"], circle["radius"]));
            }

			prop.colRects = colRects;
			prop.colCircles = colCircles;
            

            return prop;
        }

        objectData properties;
    };


    //Object Data Getter

    


  
}