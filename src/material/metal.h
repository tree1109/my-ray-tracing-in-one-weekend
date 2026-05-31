#pragma once

#ifndef INCLUDE_METAL_H
#define INCLUDE_METAL_H

#include "hittable/hittable.h"
#include "material.h"

class metal final : public material {
public:
    metal(const color& albedo, const double fuzz);

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override;

private:
    color albedo;
    double fuzz;
};

#endif // INCLUDE_METAL_H
