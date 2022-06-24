#include <Camera.h>
#include <Hitable.h>
#include <Renderer.h>
#include <SceneGenerator.h>

#include <iostream>
#include <future>
#include <chrono>

int main()
{
    int width = 800;
    int height = 400;
    int ns = 100;
    std::cout << "P3\n"
              << width << " " << height << "\n255\n";

    Hitables_t world = randomeWorld();

    Vec3_t lookFrom(13, 2, 3);
    Vec3_t lookAt(0, 0, 0);
    float distToFocus = 10.0;
    float aperture = 0.0;

    Camera camera(lookFrom, lookAt, Vec3_t(0, 1, 0), 20, float(width) / float(height), aperture, distToFocus, 0.0, 1.0);

    RenderResult_t img = renderAsync(camera, world, width, height, ns);

    for (const RayResult_t &i : img)
    {
        std::cout << i.x << " " << i.y << " " << i.z << "\n";
    }
}
