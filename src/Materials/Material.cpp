#include "Material.h"

Vec3_t Material::reflect(const Vec3_t &v, const Vec3_t &n)
{
    return v - 2 * Vec3_t::DotProduct(v, n) * n;
}

bool Material::refract(const Vec3_t &v, const Vec3_t &n, float niOverNt, Vec3_t &refracter)
{
    Vec3_t uv = v.Normalized();
    float dt = Vec3_t::DotProduct(uv, n);
    float discriminant = 1.0 - niOverNt * niOverNt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracter = Vec3_t(niOverNt) * (uv - n * Vec3_t(dt)) - n * Vec3_t(sqrt(discriminant));
        return true;
    }
    else
    {
        return false;
    }
}

float Material::schlick(float cosine, float refIdx)
{
    float r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}