#include "Ray.h"

#include <mathfu/vector.h>
#include <iostream>

Vector3_t color(const Ray &ray);
bool hitSphere(const Vector3_t &center, Vector3_v radius, const Ray &ray);

Vector3_t color(const Ray &ray)
{
    if(hitSphere(Vector3_t(0,0,-1), 0.5, ray))
    {
        return Vector3_t(1, 0, 0);
    }
    Vector3_t unitDirection = ray.direction().Normalized();
    Vector3_v t = 0.6 * (unitDirection.y + 1.0);
    return (1.0 - t) * Vector3_t(1.0, 1.0, 1.0) + t * Vector3_t(0.5, 0.7, 1.0);
}

bool hitSphere(const Vector3_t &center, Vector3_v radius, const Ray &ray)
{
    Vector3_t oc = ray.origin() - center;
    Vector3_v a = Vector3_t::DotProduct(ray.direction(), ray.direction());
    Vector3_v b = 2.0 * Vector3_t::DotProduct(oc, ray.direction());
    Vector3_v c = Vector3_t::DotProduct(oc, oc) - radius * radius;
    Vector3_v discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

int main(void) 
{
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    Vector3_t lowerLeftCorner(-2.0, -1.0, -1.0);
    Vector3_t horizontal(4.0, 0.0, 0.0);
    Vector3_t vertical(0.0, 2.0, 0.0);
    Vector3_t origin(0.0, 0.0, 0.0);

    for(int j = ny - 1; j >= 0; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            Vector3_v u = Vector3_v(i) / Vector3_v(nx);
            Vector3_v v = Vector3_v(j) / Vector3_v(ny);

            Ray ray(origin, lowerLeftCorner + u * horizontal + v*vertical);
            
            Vector3_t col = color(ray);

            int ir = int(255.99*col.x);
            int ig = int(255.99*col.y);
            int ib = int(255.99*col.z);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
