#include "ray.h"

ray::ray(const point3& origin, const vec3& direction, double time)
    : m_origin(origin)
    , m_direction(direction)
    , m_time(time) {
}

ray::ray(const point3& origin, const vec3& direction)
    : ray(origin, direction, 0){
}

const point3& ray::origin() const {
    return m_origin;
}

const vec3& ray::direction() const {
    return m_direction;
}

double ray::time() const {
    return m_time;
}

point3 ray::at(double t) const {
    return m_origin + t * m_direction;
}
