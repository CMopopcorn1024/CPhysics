#pragma once
#include <chrono>

namespace CPhysics {

    class DeltaTime {
    private:
        std::chrono::steady_clock::time_point lastTime;

    public:
        DeltaTime() {
            lastTime = std::chrono::steady_clock::now();
        }

        float getDeltaTime() {
            auto currentTime = std::chrono::steady_clock::now();
            std::chrono::duration<float> delta = currentTime - lastTime;
            lastTime = currentTime;
            return delta.count(); // seconds
        }
    };
}