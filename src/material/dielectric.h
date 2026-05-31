#pragma once

#ifndef INCLUDE_DIELECTRIC_H
#define INCLUDE_DIELECTRIC_H

#include "hittable/hittable.h"
#include "material.h"

class dielectric final : public material {
public:
    dielectric(const double refraction_index);

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override;

private:
    static double reflectance(const double cosine, const double refraction_index);

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index;
};


#endif // INCLUDE_DIELECTRIC_H
