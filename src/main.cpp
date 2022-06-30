#include <Camera.h>
#include <Hitable.h>
#include <Renderer.h>
#include <SceneGenerator.h>
#include <Images.h>

#include <iostream>
#include <future>
#include <chrono>

int main()
{   
    const int width = 1280;
    const int height = 720;
    int ns = 100;

    Hitables_t world = randomWorld();

    Vec3_t lookFrom(13, 8, 3);
    Vec3_t lookAt(0, 0, 0);
    Vec3_v distToFocus = 10.0;
    Vec3_v aperture = 0.0;

    Camera camera(lookFrom, lookAt, Vec3_t(0, 1, 0), 20, float(width) / float(height), aperture, distToFocus, 0.0, 1.0);

    RenderResult_t img = renderAsync(camera, world, width, height, ns);

    saveRenderResultPNG(img, "TraceResult.png", width, height);
}
