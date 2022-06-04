#pragma once

#include <Ray.h>
#include <Vector3.h>
#include <Hitable.h>

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
