#include <Ray.h>
#include <Sphere.h>
#include <Camera.h>
#include <Hitable.h>
#include <Renderer.h>
#include <Material.h>
#include <SceneGenerator.h>

#include <mathfu/vector.h>
#include <iostream>

int main(void)
{
    int width = 400;
    int height = 200;
    int ns = 100;
    std::cout << "P3\n"
              << width << " " << height << "\n255\n";

    HitableArr_t scene = randomeScene();

    Vec3_t lookFrom(8, 4, 1);
    Vec3_t lookAt(0, 0, -1);
    float distToFocus = (lookFrom - lookAt).Length();
    float aperture = 2.0;

    Camera camera(lookFrom, lookAt, Vec3_t(0, 1, 0), 40, float(width) / float(height), aperture, distToFocus);

    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            Vec3_t col(0, 0, 0);
            for (int s = 0; s < ns; s++)
            {
                Vec3_v u = Vec3_v(i + drand48()) / Vec3_v(width);
                Vec3_v v = Vec3_v(j + drand48()) / Vec3_v(height);
                Ray ray = camera.getRay(u, v);
                col += render(ray, scene, 0);
            }
            col /= Vec3_v(ns);
            col = Vec3_t(sqrt(col.x), sqrt(col.y), sqrt(col.z));

            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
