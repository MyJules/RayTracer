#include "Camera.h"

Camera::Camera()
{
    origin = Vec3_t(0.0, 0.0, 0.0);
    lowerLeftCorner = Vec3_t(-2.0, -1.0, -1.0);
    horizontal = Vec3_t(4.0, 0.0, 0.0);
    vertical = Vec3_t(0.0, 2.0, 0.0);
}

Ray Camera::getRay(Vec3_v u, Vec3_v v)
{
    return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
}