#pragma once

#include <vector>
#include <cmath>


#include <CPhysics/Vector2.h>

namespace CPhysics
{

    struct PerlinSettings
    {
        int seed = 0;

        float scale = 400.0f;

        int octaves = 6;

        float persistence = 0.5f;
        float lacunarity = 2.0f;

        float amplitude = 1.0f;

        float offsetX = 0.0f;
        float offsetY = 0.0f;

        bool normalize = true;

        // Controls terrain shape
        // 1 = normal
        // >1 = flatter
        // <1 = sharper
        float exponent = 1.0f;
    };


    class Perlin
    {
    public:

        static std::vector<float> GeneratePerlin(
            int width,
            int height,
            const PerlinSettings& settings
        );

        
    private:

        static Vector2 randomGradient(
            int ix,
            int iy,
            int seed
        );


        static float dotGridGradient(
            int ix,
            int iy,
            float x,
            float y,
            int seed
        );


        static float samplePerlin(
            float x,
            float y,
            int seed
        );


        static float fade(float t);


        static float lerp(
            float a,
            float b,
            float t
        );
    };

}