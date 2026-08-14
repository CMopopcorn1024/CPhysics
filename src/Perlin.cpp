#include <CPhysics/Perlin.h>

#include <cmath>


namespace CPhysics
{


std::vector<float> Perlin::GeneratePerlin(
    int width,
    int height,
    const PerlinSettings& settings
)
{
    std::vector<float> noise(width * height);


    float maxAmplitude = 0.0f;


    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {

            float value = 0.0f;

            float frequency = 1.0f;
            float amplitude = 1.0f;


            for(int octave = 0;
                octave < settings.octaves;
                octave++)
            {

                float sampleX =
                    (x + settings.offsetX)
                    * frequency
                    / settings.scale;


                float sampleY =
                    (y + settings.offsetY)
                    * frequency
                    / settings.scale;



                value += samplePerlin(
                    sampleX,
                    sampleY,
                    settings.seed
                )
                * amplitude;



                maxAmplitude += amplitude;


                amplitude *= settings.persistence;

                frequency *= settings.lacunarity;
            }


            if(settings.normalize)
            {
                value /= maxAmplitude;
            }


            value *= settings.amplitude;



            // Terrain shaping
            if(settings.exponent != 1.0f)
            {
                float normalized =
                    (value + 1.0f) * 0.5f;


                normalized =
                    std::pow(
                        normalized,
                        settings.exponent
                    );


                value =
                    normalized * 2.0f - 1.0f;
            }



            noise[y * width + x] = value;
        }
    }


    return noise;
}



Vector2 Perlin::randomGradient(
    int ix,
    int iy,
    int seed
)
{

    unsigned a = ix;
    unsigned b = iy;


    // Add seed randomness
    a += seed * 374761393;
    b += seed * 668265263;


    a *= 3284157443u;


    b ^= (a << 16) | (a >> 16);


    b *= 1911520717u;


    a ^= (b << 16) | (b >> 16);


    a *= 2048419325u;


    float random =
        a * (3.14159265359f /
        ~(~0u >> 1));



    return Vector2(
        std::cos(random),
        std::sin(random)
    );
}



float Perlin::dotGridGradient(
    int ix,
    int iy,
    float x,
    float y,
    int seed
)
{

    Vector2 gradient =
        randomGradient(
            ix,
            iy,
            seed
        );


    Vector2 distance(
        x - ix,
        y - iy
    );


    return Vector2::Dot(gradient,distance);
}



float Perlin::fade(float t)
{
    // Quintic interpolation
    return t * t * t *
        (t * (t * 6 - 15) + 10);
}



float Perlin::lerp(
    float a,
    float b,
    float t
)
{
    return a + t * (b - a);
}



float Perlin::samplePerlin(
    float x,
    float y,
    int seed
)
{

    int x0 = (int)std::floor(x);
    int y0 = (int)std::floor(y);


    int x1 = x0 + 1;
    int y1 = y0 + 1;



    float sx =
        fade(x - x0);

    float sy =
        fade(y - y0);



    float n0 =
        dotGridGradient(
            x0,
            y0,
            x,
            y,
            seed
        );


    float n1 =
        dotGridGradient(
            x1,
            y0,
            x,
            y,
            seed
        );


    float ix0 =
        lerp(
            n0,
            n1,
            sx
        );



    float n2 =
        dotGridGradient(
            x0,
            y1,
            x,
            y,
            seed
        );


    float n3 =
        dotGridGradient(
            x1,
            y1,
            x,
            y,
            seed
        );


    float ix1 =
        lerp(
            n2,
            n3,
            sx
        );



    return lerp(
        ix0,
        ix1,
        sy
    );
}





}