#pragma once

#ifndef INCLUDE_HITTABLE_H
#define INCLUDE_HITTABLE_H

#include "rtweekend.h"

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

public:
    virtual bool hit(const ray& r, const double ray_t_min, const double ray_t_max, hit_record& record) const = 0;
};


#endif // INCLUDE_HITTABLE_H
