#pragma once

#ifndef INCLUDE_AABB_H
#define INCLUDE_AABB_H
#include "interval.h"
#include "ray.h"
#include "vec3.h"

class aabb
{
public:
    // The default AABB is empty, since intervals are empty by default.
    aabb() = default;

    aabb(const interval& x, const interval& y, const interval& z);

    aabb(const point3& a, const point3& b);

    const interval& axis_interval(int n) const;

    bool hit(const ray& r, interval ray_t) const;

public:
    interval x;
    interval y;
    interval z;
};

#endif //INCLUDE_AABB_H
