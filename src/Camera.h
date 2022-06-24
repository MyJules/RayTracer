#pragma once

#include <Vector3.h>
#include <Ray.h>

// Handles camera math
class Camera
{
public:
    Camera(Vec3_t lookFrom, Vec3_t lookAt, Vec3_t up, float vfov, float aspect, float aperture, float focusDistance, float time1, float time2);

    Ray getRay(Vec3_v u, Vec3_v v) const;

    Vec3_t m_origin;
    Vec3_t m_lowerLeftCorner;
    Vec3_t m_horizontal;
    Vec3_t m_vertical;
    float m_lensRadius;
    float m_time1;
    float m_time2;
};
