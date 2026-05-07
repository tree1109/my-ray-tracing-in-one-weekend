#pragma once

#ifndef INCLUDE_SPHERE_H
#define INCLUDE_SPHERE_H

#include "hittable.h"

class sphere final : public hittable {
public:
    sphere(const point3& center, const double radius) : center(center), radius(std::max(radius, 0.0)) {}

    bool hit(const ray& r, const interval& ray_t, hit_record& record) const override {
        const vec3 oc  = center - r.origin();
        const double a = r.direction().length_squared();
        const double h = dot(r.direction(), oc);
        const double c = dot(oc, oc) - radius * radius;

        const double discriminant = h * h - a * c;
        if (discriminant < 0.0) {
            return false;
        }

        const double sqrt_d = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (h - sqrt_d) / a;
        if (!ray_t.surrounds(root)) {
            root = (h + sqrt_d) / a;
            if (!ray_t.surrounds(root)) {
                return false;
            }
        }

        record.t      = root;
        record.p      = r.at(record.t);
        vec3 outward_normal =  (record.p - center) / radius;
        record.set_face_normal(r, outward_normal);

        return true;
    }

private:
    point3 center;
    double radius;
};

#endif // INCLUDE_SPHERE_H
