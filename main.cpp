#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"

#include <mathfu/vector.h>
#include <iostream>

Vec3_t color(const Ray &ray, const HitableArr_t &world)
{
    HitRecord rec;
    bool hitAnything = false;
    Vec3_v closest = MAXFLOAT;
    HitRecord closestRec;

    for(const auto &surface : world)
    {
        if(surface->hit(ray, 0.0, MAXFLOAT, rec))
        {
            hitAnything = true;
            if(closest > rec.t)
            {
                closest = rec.t;
                closestRec = rec;
            }
        }
    }

    if(hitAnything)
    {
        return 0.5 * Vec3_t(closestRec.normal.x+1, closestRec.normal.y+1, closestRec.normal.z+1);
    }

    //if nothing found draw background
    Vec3_t unitDirection = ray.direction().Normalized();
    Vec3_v t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Vec3_t(1.0, 1.0, 1.0) + t * Vec3_t(0.5, 0.7, 1.0);
}

int main(void) 
{
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    Vec3_t lowerLeftCorner(-2.0, -1.0, -1.0);
    Vec3_t horizontal(4.0, 0.0, 0.0);
    Vec3_t vertical(0.0, 2.0, 0.0);
    Vec3_t origin(0.0, 0.0, 0.0);

    HitableArr_t world;
    world.emplace_back(new Sphere(Vec3_t(0.0, -100.5, -1.0), 100));
    world.emplace_back(new Sphere(Vec3_t(0.0, 0.0, -1.0), 0.5));

    for(int j = ny - 1; j >= 0; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            Vec3_v u = Vec3_v(i) / Vec3_v(nx);
            Vec3_v v = Vec3_v(j) / Vec3_v(ny);

            Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
            
            Vec3_t col = color(ray, world);

            int ir = int(255.99*col.x);
            int ig = int(255.99*col.y);
            int ib = int(255.99*col.z);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
