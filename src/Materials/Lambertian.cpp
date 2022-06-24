#include "Lambertian.h"

bool Lambertian::scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const
{
    Vec3_t target = rec.p + rec.normal + randomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p, ray.time());
    attenuation = m_albedo;
    return true;
}