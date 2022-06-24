#include "Renderer.h"

#include <Material.h>
#include <Camera.h>

#include <BS_thread_pool.hpp>

#include <future>
#include <thread>
#include <chrono>

Vec3_t color(const Ray &ray, const Hitables_t &world, int depth)
{
    HitRecord rec;
    bool hitAnything = false;
    Vec3_v closest = MAXFLOAT;
    HitRecord closestRec;

    for (const auto &surface : world)
    {
        if (surface->hit(ray, 0.001, MAXFLOAT, rec))
        {
            hitAnything = true;
            if (closest > rec.t)
            {
                closest = rec.t;
                closestRec = rec;
            }
        }
    }

    if (hitAnything)
    {
        Ray scattered;
        Vec3_t attenuation;
        if (depth < 80 && closestRec.material->scatter(ray, closestRec, attenuation, scattered))
        {
            // Vec3_t target = rec.p + rec.normal + randomInUnitSphere();
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return Vec3_t(0, 0, 0);
        }
    }

    // if nothing found draw background
    Vec3_t unitDirection = ray.direction().Normalized();
    Vec3_v t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Vec3_t(1.0, 1.0, 1.0) + t * Vec3_t(0.5, 0.7, 1.0);
}

Vec3_t randomInUnitSphere()
{
    Vec3_t p;
    do
    {
        p = 2.0 * Vec3_t(drand48(), drand48(), drand48()) - Vec3_t(1.0, 1.0, 1.0);
    } while (p.LengthSquared() >= 1.0);
    return p;
}

// Function to render scene
RenderResult_t render(const Camera &camera, const Hitables_t &scene, int width, int height, int ns)
{
    RenderResult_t res;

    int pixelCount = width * height;
    res.reserve(pixelCount);

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
                col += color(ray, scene, 0);
            }
            col /= Vec3_v(ns);
            col = Vec3_t(sqrt(col.x), sqrt(col.y), sqrt(col.z));

            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);
            res.push_back(Vec3_t(ir, ig, ib));
        }
    }
    return res;
}

// Render scene on different threads
RenderResult_t renderAsync(const Camera &camera, const Hitables_t &scene, int width, int height, int ns)
{
    BS::multi_future<Vec3_t> mf;
    BS::thread_pool pool(std::thread::hardware_concurrency());

    for (int j = height - 1; j >= 0; j--)
    {
        for (int i = 0; i < width; i++)
        {
            mf.f.push_back(
                pool.submit(
                    [i, j, ns, &camera, &scene, width, height]() -> Vec3_t
                    {
                    Vec3_t col(0, 0, 0);
                    for (int s = 0; s < ns; s++)
                    {
                        Vec3_v u = Vec3_v(i + drand48()) / Vec3_v(width);
                        Vec3_v v = Vec3_v(j + drand48()) / Vec3_v(height);
                        Ray ray = camera.getRay(u, v);
                        col += color(ray, scene, 0);
                    }
                    col /= Vec3_v(ns);
                    col = Vec3_t(sqrt(col.x), sqrt(col.y), sqrt(col.z));

                    int ir = int(255.99 * col.x);
                    int ig = int(255.99 * col.y);
                    int ib = int(255.99 * col.z);

                    return Vec3_t(ir, ig, ib);
            }));
        }
    }

    return mf.get();
}
