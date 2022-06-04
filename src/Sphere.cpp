#include "Sphere.h"

bool Sphere::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const
{
    Vec3_t oc = ray.origin() - m_center;
    Vec3_v a = Vec3_t::DotProduct(ray.direction(), ray.direction());
    Vec3_v b = Vec3_t::DotProduct(oc, ray.direction());
    Vec3_v c = Vec3_t::DotProduct(oc, oc) - m_radius * m_radius;
    Vec3_v discriminant = b * b -  a * c;

    if(discriminant > 0)
    {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = ray.pointAtParameter(record.t);
            record.normal = (record.p - m_center) / Vec3_t(m_radius, m_radius, m_radius);
            return true;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = ray.pointAtParameter(record.t);
            record.normal = (record.p - m_center) / Vec3_t(m_radius, m_radius, m_radius);
            return true;
        }
    }

    return false;
}