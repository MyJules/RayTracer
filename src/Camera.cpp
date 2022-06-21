#include "Camera.h"

#include <Renderer.h>

Camera::Camera(Vec3_t lookFrom, Vec3_t lookAt, Vec3_t up, float vfov, float aspect, float aperture, float focusDistance)
{
    Vec3_t u, v, w;
    float theta = vfov*M_PI/180;
    float halfHeight = tan(theta/2);
    float halfWidth = aspect * halfHeight;

    m_lensRadius = aperture/2;
    
    m_origin = lookFrom;

    w = (lookFrom - lookAt).Normalized();
    u = Vec3_t::CrossProduct(up, w).Normalized();
    v = Vec3_t::CrossProduct(w, u);

    m_lowerLeftCorner = Vec3_t(-halfWidth, -halfHeight, -1.0);
    m_lowerLeftCorner = m_origin - Vec3_t(halfWidth)*u - Vec3_t(halfHeight)*v - w;
    m_horizontal = Vec3_t(2)*Vec3_t(halfWidth)*u;
    m_vertical = Vec3_t(2)*Vec3_t(halfHeight)*v;

}

Ray Camera::getRay(Vec3_v u, Vec3_v v) const
{
    Vec3_t rd = Vec3_t(m_lensRadius)*randomInUnitSphere();
    Vec3_t offset = Vec3_t(u) * Vec3_t(rd.x) + Vec3_t(v) * Vec3_t(rd.y);
    return Ray(m_origin, m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin);
}