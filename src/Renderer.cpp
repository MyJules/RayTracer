#include "Renderer.h"

#include <Material.h>

Vec3_t render(const Ray &ray, const HitableArr_t &world, int depth)
{
    HitRecord rec;
    bool hitAnything = false;
    Vec3_v closest = MAXFLOAT;
    HitRecord closestRec;

    for(const auto &surface : world)
    {
        if(surface->hit(ray, 0.001, MAXFLOAT, rec))
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
        Ray scattered;
        Vec3_t attenuation; 
        if(depth < 80 && closestRec.material->scatter(ray, closestRec, attenuation, scattered))
        {
            //Vec3_t target = rec.p + rec.normal + randomInUnitSphere();
            return attenuation * render(scattered, world, depth + 1);
        }else
        {
            return Vec3_t(0, 0, 0);
        }
    }

    //if nothing found draw background
    Vec3_t unitDirection = ray.direction().Normalized();
    Vec3_v t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Vec3_t(1.0, 1.0, 1.0) + t * Vec3_t(0.5, 0.7, 1.0);
}

Vec3_t randomInUnitSphere()
{
    Vec3_t p;
    do
    {
        p = 2.0*Vec3_t(drand48(), drand48(), drand48()) - Vec3_t(1.0, 1.0, 1.0);
    } while (p.LengthSquared() >= 1.0);
    return p;
}