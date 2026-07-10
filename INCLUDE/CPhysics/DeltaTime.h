#pragma once
#include <chrono>

namespace CPhysics {

    class DeltaTime 
    {
    private:
        std::chrono::steady_clock::time_point lastTime;

    public:
        DeltaTime();

        float getDeltaTime();
    };
}