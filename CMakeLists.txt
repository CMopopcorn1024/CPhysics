cmake_minimum_required(VERSION 3.20)

project(CPhysics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(external/raylib)

# Create static library
add_library(CPhysics STATIC
    CPhysics/Circle.cpp
    CPhysics/CollisionObject.cpp
    CPhysics/Object.cpp
    CPhysics/ObjectCreation.cpp
    CPhysics/PhysicsObject.cpp
    CPhysics/Rectangle.cpp
    CPhysics/Segment.cpp
    CPhysics/Vector2.cpp

)

# Tell projects using CPhysics where the headers are
target_include_directories(CPhysics PUBLIC
    CPhysics
    external/nlohmann-json/single_include
)

target_link_libraries(CPhysics PUBLIC
    raylib
)
