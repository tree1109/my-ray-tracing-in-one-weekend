#pragma once

#ifndef INCLUDE_HITTABLE_H
#define INCLUDE_HITTABLE_H

#include "interval.h"
#include "ray.h"
#include <memory>

#include "aabb.h"

class material;

class hit_record {
public:
    void set_face_normal(const ray& r, const vec3& outward_normal);

public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
    double t;
    bool front_face;
};

class hittable {
public:
    virtual ~hittable() = default;

public:
    virtual bool hit(const ray& r, const interval& ray_t, hit_record& record) const = 0;

    virtual aabb bounding_box() const = 0;
};


#endif // INCLUDE_HITTABLE_H
