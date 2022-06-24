#include "SceneGenerator.h"

#include <Hitable.h>
#include <Vector3.h>
#include <Sphere.h>
#include <MovingSphere.h>

#include <Metal.h>
#include <Dielectric.h>
#include <Lambertian.h>

// Returns world to render
Hitables_t randomeWorld()
{
    Hitables_t res;
    res.emplace_back(std::make_unique<Sphere>(Vec3_t(0.0, -1000, 0.0), 1000, std::make_shared<Lambertian>(Vec3_t(0.5, 0.5, 0.5))));

    for (int a = -18; a < 18; a++)
    {
        for (int b = -18; b < 18; b++)
        {
            float chooseMat = drand48();
            Vec3_t center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - Vec3_t(4, 0.2, 0)).Length() > 0.9)
            {
                if (chooseMat < 0.8) // diffuse
                {
                    res.emplace_back(std::make_unique<MovingSphere>(
                        center, center + Vec3_t(0, 0.5 * drand48(), 0), 0.0, 1.0, 0.2, std::make_shared<Lambertian>(Vec3_t(drand48() * drand48(), drand48() * drand48(), drand48() * drand48()))));
                }
                else if (chooseMat < 0.95) // metal
                {
                    res.emplace_back(std::make_unique<Sphere>(
                        center, 0.2, std::make_shared<Metal>(Vec3_t(1 + drand48(), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48())));
                }
                else // glass
                {
                    res.emplace_back(std::make_unique<Sphere>(
                        center, 0.2, std::make_shared<Dielectric>(1.5)));
                }
            }
        }
    }

    res.emplace_back(std::make_unique<Sphere>(Vec3_t(0, 1, 0), 1.0, std::make_unique<Dielectric>(1.5)));
    res.emplace_back(std::make_unique<Sphere>(Vec3_t(-4, 1, 0), 1.0, std::make_unique<Lambertian>(Vec3_t(0.4, 0.2, 0.1))));
    res.emplace_back(std::make_unique<Sphere>(Vec3_t(4, 1, 0), 1.0, std::make_unique<Metal>(Vec3_t(0.7, 0.6, 0.5), 0.0)));

    return res;
}