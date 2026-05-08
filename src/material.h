#pragma once

#ifndef INCLUDE_MATERIAL_H
#define INCLUDE_MATERIAL_H

#include "hittable.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const {
        return false;
    }
};

class lambertial final : public material {
public:
    lambertial(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override {
        auto scatter_direction = record.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(record.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif // INCLUDE_MATERIAL_H
