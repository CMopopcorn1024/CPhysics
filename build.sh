#!/bin/bash

mkdir -p build

clang++ \
-std=c++17 \
Game/src/main.cpp \
Physics/src/PhysicsObject.cpp \
Physics/src/CollisionObject.cpp \
Physics/src/DeltaTime.cpp \
-o build/game \
-IPhysics/include \
-IGame/include \
-I$RAYLIB_PATH/include \
-L$RAYLIB_PATH/lib \
-lraylib \
-framework OpenGL \
-framework IOKit \
-framework Cocoa \
-framework CoreVideo