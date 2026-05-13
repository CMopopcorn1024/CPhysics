#!/bin/bash

set -e

RAYLIB_PATH=$(brew --prefix raylib)

mkdir -p build

clang++ \
-std=c++17 \
$(find Game -name "*.cpp") \
$(find CPhysics -name "*.cpp") \
-o build/game \
-I./CPhysics \
-I/opt/homebrew/include \
-I$RAYLIB_PATH/include \
-L$RAYLIB_PATH/lib \
-lraylib \
-framework OpenGL \
-framework IOKit \
-framework Cocoa \
-framework CoreVideo