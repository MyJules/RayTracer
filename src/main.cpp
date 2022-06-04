#include <Ray.h>
#include <Hitable.h>
#include <Sphere.h>
#include <Renderer.h>
#include <Camera.h>
#include <Material.h>

#include <mathfu/vector.h>
#include <iostream>

int main(void) 
{
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    HitableArr_t world;
    world.emplace_back(std::make_unique<Sphere>(Vec3_t(0.0, -100.5, -1.0), 100, std::make_shared<Lambertian>(Vec3_t(0.8, 0.8, 0.0))));
    world.emplace_back(std::make_unique<Sphere>(Vec3_t(0.0, 0.0, -1.0), 0.5,  std::make_shared<Lambertian>(Vec3_t(0.8, 0.3, 0.3))));
    // world.emplace_back(std::make_unique<Sphere>(Vec3_t(1.0, 0.0, -1.0), 0.5,  std::make_shared<Metal>(Vec3_t(0.8, 0.6, 0.2))));
    // world.emplace_back(std::make_unique<Sphere>(Vec3_t(-1.0, 0.0, -1.0), 0.5,  std::make_shared<Metal>(Vec3_t(0.8, 0.8, 0.8))));
    
    Camera camera;

    for(int j = ny - 1; j >= 0; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            Vec3_t col(0, 0, 0);
            for(int s = 0; s < ns; s++)
            {
                Vec3_v u = Vec3_v(i + drand48()) / Vec3_v(nx);
                Vec3_v v = Vec3_v(j + drand48()) / Vec3_v(ny);
                Ray ray = camera.getRay(u, v);
                col += color(ray, world, 0);
            }
            col /= Vec3_v(ns);
            col = Vec3_t(sqrt(col.x), sqrt(col.y), sqrt(col.z));

            int ir = int(255.99*col.x);
            int ig = int(255.99*col.y);
            int ib = int(255.99*col.z);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
