#include "Dielectric.h"

bool Dielectric::scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const
{
    Vec3_t outwardNormal;
    Vec3_t reflected = Material::reflect(ray.direction(), rec.normal);
    float niOverNt;
    attenuation = Vec3_t(1.0, 1.0, 1.0);
    Vec3_t refracter;
    float reflectProb;
    float cosine;
    if (Vec3_t::DotProduct(ray.direction(), rec.normal) > 0)
    {
        outwardNormal = -rec.normal;
        niOverNt = m_refIdx;
        cosine = m_refIdx * Vec3_t::DotProduct(ray.direction(), rec.normal) / ray.direction().Length();
    }
    else
    {
        outwardNormal = rec.normal;
        niOverNt = 1.0 / m_refIdx;
        cosine = -Vec3_t::DotProduct(ray.direction(), rec.normal) / ray.direction().Length();
    }

    if (refract(ray.direction(), outwardNormal, niOverNt, refracter))
    {
        reflectProb = Material::schlick(cosine, m_refIdx);
    }
    else
    {
        scattered = Ray(rec.p, reflected);
        reflectProb = 1.0;
    }

    if (drand48() < reflectProb)
    {
        scattered = Ray(rec.p, reflected);
    }
    else
    {
        scattered = Ray(rec.p, refracter);
    }

    return true;
}