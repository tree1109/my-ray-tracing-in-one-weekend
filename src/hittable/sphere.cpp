#include "sphere.h"

sphere::sphere(const point3& center, double radius, std::shared_ptr<material> mat)
    : center(center, vec3(0, 0, 0))
    , radius(std::fmax(radius, 0))
    , mat(std::move(mat)) {
    const vec3 radius_vec = vec3(radius, radius, radius);
    bbox            = aabb(center - radius_vec, center + radius_vec);
}

sphere::sphere(const point3& from_center, const point3& to_center, double radius, std::shared_ptr<material> mat)
    : center(from_center, to_center - from_center)
    , radius(std::fmax(radius, 0))
    , mat(std::move(mat)) {
    const vec3 radius_vec = vec3(radius, radius, radius);
    const aabb box1(center.at(0) - radius_vec, center.at(0) + radius_vec);
    const aabb box2(center.at(1) - radius_vec, center.at(1) + radius_vec);
    bbox            = aabb(box1, box2);
}

bool sphere::hit(const ray& r, const interval& ray_t, hit_record& record) const {
    const point3 current_center = center.at(r.time());
    const vec3 oc               = current_center - r.origin();
    const double a              = r.direction().length_squared();
    const double h              = dot(r.direction(), oc);
    const double c              = dot(oc, oc) - radius * radius;

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
    vec3 outward_normal = (record.p - current_center) / radius;
    record.set_face_normal(r, outward_normal);
    record.mat = mat;

    return true;
}

aabb sphere::bounding_box() const {
    return bbox;
}
