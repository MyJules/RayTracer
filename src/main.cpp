#include <Camera.h>
#include <Hitable.h>
#include <Renderer.h>
#include <SceneGenerator.h>

#include <iostream>
#include <future>
#include <chrono>

int main(void)
{
    int width = 200;
    int height = 100;
    int ns = 100;
    std::cout << "P3\n"
              << width << " " << height << "\n255\n";

    Hitables_t world = randomeWorld();

    Vec3_t lookFrom(6, 3, 4);
    Vec3_t lookAt(0, 0, -1);
    float distToFocus = (lookFrom - lookAt).Length();
    float aperture = 2.0;

    Camera camera(lookFrom, lookAt, Vec3_t(0, 1, 0), 40, float(width) / float(height), aperture, distToFocus);

    RenderResult_t img = renderAsync(camera, world, width, height, ns);

    for (const RayResult_t &i : img)
    {
        std::cout << i.x << " " << i.y << " " << i.z << "\n";
    }
}
