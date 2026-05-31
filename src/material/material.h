#pragma once

#ifndef INCLUDE_MATERIAL_H
#define INCLUDE_MATERIAL_H

#include "utility.h"
#include "texture/solid_color.h"
#include "texture/texture.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const {
        return false;
    }
};

class lambertian final : public material {
public:
    lambertian(const color& albedo) : tex(std::make_shared<solid_color>(albedo)) {}
    lambertian(const std::shared_ptr<texture>& albedo) : tex(albedo) {}

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override {
        auto scatter_direction = record.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = record.normal;

        scattered = ray(record.p, scatter_direction, r_in.time());
        attenuation = tex->value(record.u, record.v, record.p);
        return true;
    }

private:
    std::shared_ptr<texture> tex;
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
        scattered = ray(record.p, reflected, r_in.time());
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

        if (cannot_refract || reflectance(cos_theta, ri) > random_double()) {
            direction = reflect(unit_direction, record.normal);
        }
        else {
            direction = refract(unit_direction, record.normal, ri);
        }

        scattered = ray(record.p, direction, r_in.time());
        return true;
    }

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;

    static double reflectance(const double cosine, const double refraction_index) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1 - cosine),5);
    }
};

#endif // INCLUDE_MATERIAL_H
