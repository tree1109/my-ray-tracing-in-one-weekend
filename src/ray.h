#pragma once

#ifndef INCLUDE_RAY_H
#define INCLUDE_RAY_H

#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction);

    [[nodiscard]] const point3& origin() const;

    [[nodiscard]] const vec3& direction() const;

    [[nodiscard]] point3 at(double t) const;

private:
    point3 m_origin;
    vec3 m_direction;
};

#endif // INCLUDE_RAY_H
