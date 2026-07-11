cmake_minimum_required(VERSION 3.20)

project(CPhysics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(CPhysics STATIC
    src/Circle.cpp
    src/CollisionObject.cpp
    src/Object.cpp
    src/ObjectCreation.cpp
    src/PhysicsObject.cpp
    src/Rectangle.cpp
    src/Segment.cpp
    src/Vector2.cpp
    src/DeltaTime.cpp
)

target_include_directories(CPhysics PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../nlohmann-json/single_include
)

target_link_libraries(CPhysics PUBLIC
    raylib
)