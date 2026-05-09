#include "sphere.h"

sphere::sphere(const point3& center, double radius, std::shared_ptr<material> mat)
    : center(center)
    , radius(std::max(radius, 0.0))
    , mat(mat) {
}

bool sphere::hit(const ray& r, const interval& ray_t, hit_record& record) const {
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

    record.t            = root;
    record.p            = r.at(record.t);
    vec3 outward_normal = (record.p - center) / radius;
    record.set_face_normal(r, outward_normal);
    record.mat = mat;

    return true;
}
