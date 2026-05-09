#pragma once

#ifndef INCLUDE_SPHERE_H
#define INCLUDE_SPHERE_H

#include "hittable.h"
#include <memory>

class sphere final : public hittable {
public:
    sphere(const point3& center, double radius, std::shared_ptr<material> mat);

    bool hit(const ray& r, const interval& ray_t, hit_record& record) const override;

private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
};

#endif // INCLUDE_SPHERE_H
