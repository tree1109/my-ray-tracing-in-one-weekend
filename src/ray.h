#pragma once

#ifndef INCLUDE_RAY_H
#define INCLUDE_RAY_H
#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction) : m_origin(origin), m_direction(direction) {}

    [[nodiscard]] const point3& origin() const {
        return m_origin;
    }
    [[nodiscard]] const vec3& direction() const {
        return m_direction;
    }

    [[nodiscard]] point3 at(const double t) const {
        return m_origin + t * m_direction;
    }

private:
    point3 m_origin;
    vec3 m_direction;
};

#endif // INCLUDE_RAY_H
