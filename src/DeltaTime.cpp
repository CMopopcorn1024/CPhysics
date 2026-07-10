#include "DeltaTime.h"


namespace CPhysics
{


    DeltaTime::DeltaTime() {
        lastTime = std::chrono::steady_clock::now();
    }

    float DeltaTime::getDeltaTime() {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> delta = currentTime - lastTime;
        lastTime = currentTime;
        return delta.count(); // seconds
    }


}