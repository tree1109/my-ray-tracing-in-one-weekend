#pragma once

#ifndef INCLUDE_SPHERE_H
#define INCLUDE_SPHERE_H

#include "hittable.h"
#include <memory>

class sphere final : public hittable {
public:
    // Stationary Sphere
    sphere(const point3& static_center, double radius, std::shared_ptr<material> mat);

    // Moving Sphere
    sphere(const point3& from_center, const point3& to_center, double radius, std::shared_ptr<material> mat);

    bool hit(const ray& r, const interval& ray_t, hit_record& record) const override;

private:
    ray center;
    double radius;
    std::shared_ptr<material> mat;
};

#endif // INCLUDE_SPHERE_H
