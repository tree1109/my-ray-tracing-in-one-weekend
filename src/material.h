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

class dielectric final : public material {
public:
    dielectric(const double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double ri = record.front_face ? (1.0 / refraction_index) : refraction_index;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = std::min(dot(-unit_direction, record.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract) {
            direction = reflect(unit_direction, record.normal);
        }
        else {
            direction = refract(unit_direction, record.normal, ri);
        }

        scattered = ray(record.p, direction);
        return true;
    }

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;
};

#endif // INCLUDE_MATERIAL_H
