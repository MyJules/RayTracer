#include "Metal.h"

Metal::Metal(const Vec3_t &a, float fuzz) : m_albedo(a)
{
    if (fuzz < 1)
    {
        m_fuzz = fuzz;
    }
    else
    {
        m_fuzz = 1;
    }
}

bool Metal::scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const
{
    Vec3_t reflected = Material::reflect(ray.direction().Normalized(), rec.normal);
    scattered = Ray(rec.p, reflected + Vec3_t(m_fuzz) * randomInUnitSphere());
    attenuation = m_albedo;
    return Vec3_t::DotProduct(scattered.direction(), rec.normal) > 0;
}