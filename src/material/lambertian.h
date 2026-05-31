#pragma once

#ifndef INCLUDE_LAMBERTIAN_H
#define INCLUDE_LAMBERTIAN_H

#include "hittable/hittable.h"
#include "material.h"

class lambertian final : public material {
public:
    lambertian(const color& albedo);
    lambertian(const std::shared_ptr<texture>& albedo);

    bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const override;

private:
    std::shared_ptr<texture> tex;
};

#endif // INCLUDE_LAMBERTIAN_H
