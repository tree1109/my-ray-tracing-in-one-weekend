#include "lambertian.h"

#include "texture/solid_color.h"

lambertian::lambertian(const color& albedo) : tex(std::make_shared<solid_color>(albedo)) {}

lambertian::lambertian(const std::shared_ptr<texture>& albedo) : tex(albedo) {}

bool lambertian::scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const {
    auto scatter_direction = record.normal + random_unit_vector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero()) {
        scatter_direction = record.normal;
    }

    scattered   = ray(record.p, scatter_direction, r_in.time());
    attenuation = tex->value(record.u, record.v, record.p);
    return true;
}
