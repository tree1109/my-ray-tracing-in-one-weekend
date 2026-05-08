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

class lambertian final : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override {
        auto scatter_direction = record.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = record.normal;

        scattered = ray(record.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

class metal final : public material {
public:
    metal(const color& albedo, const double fuzz)
        : albedo(albedo)
        , fuzz(fuzz < 1.0 ? fuzz : 1.0) {
    }

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), record.normal);
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = ray(record.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), record.normal) > 0;
    }

private:
    color albedo;
    double fuzz;
};

#endif // INCLUDE_MATERIAL_H
