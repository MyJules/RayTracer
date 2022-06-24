#include "MovingSphere.h"

MovingSphere::MovingSphere(Vec3_t center1, Vec3_t center2, float time1, float time2, float radius, std::shared_ptr<Material> material)
    : m_center1(center1), m_center2(center2), m_time1(time1), m_time2(time2), m_radius(radius), m_material(material)
{
}

bool MovingSphere::hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const
{
    Vec3_t oc = ray.origin() - center(ray.time());
    Vec3_v a = Vec3_t::DotProduct(ray.direction(), ray.direction());
    Vec3_v b = Vec3_t::DotProduct(oc, ray.direction());
    Vec3_v c = Vec3_t::DotProduct(oc, oc) - m_radius * m_radius;
    Vec3_v discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - sqrt(b * b - a * c)) / a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = ray.pointAtParameter(record.t);
            record.normal = (record.p - center(ray.time())) / Vec3_t(m_radius, m_radius, m_radius);
            record.material = m_material;
            return true;
        }
        temp = (-b + sqrt(b * b - a * c)) / a;
        if (temp < tMax && temp > tMin)
        {
            record.t = temp;
            record.p = ray.pointAtParameter(record.t);
            record.normal = (record.p - center(ray.time())) / Vec3_t(m_radius, m_radius, m_radius);
            record.material = m_material;
            return true;
        }
    }

    return false;
}

Vec3_t MovingSphere::center(float time) const
{
    return m_center1 + Vec3_t(((time - m_time1) / (m_time2 - m_time1))) * (m_center2 - m_center1);
}
