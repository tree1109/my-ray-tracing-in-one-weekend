#include "metal.h"

metal::metal(const color& albedo, const double fuzz) : albedo(albedo), fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

bool metal::scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const {
    vec3 reflected = reflect(r_in.direction(), record.normal);
    reflected      = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered      = ray(record.p, reflected, r_in.time());
    attenuation    = albedo;
    return dot(scattered.direction(), record.normal) > 0;
}
