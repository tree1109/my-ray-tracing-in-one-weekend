#include "vec3.h"

#include "utility.h"
#include <algorithm>

vec3::vec3()
    : e{0, 0, 0} {
}

vec3::vec3(double x, double y, double z)
    : e{x, y, z} {
}

double vec3::x() const {
    return e[0];
}

double vec3::y() const {
    return e[1];
}

double vec3::z() const {
    return e[2];
}

vec3 vec3::operator-() const {
    return vec3{-e[0], -e[1], -e[2]};
}

double vec3::operator[](int i) const {
    return e[i];
}

double& vec3::operator[](int i) {
    return e[i];
}

vec3& vec3::operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator*=(const vec3& v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

double vec3::length() const {
    return std::sqrt(length_squared());
}

double vec3::length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

bool vec3::near_zero() const {
    // Return true if the vector is close to zero in all dimensions.
    auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
}

vec3 vec3::random() {
    return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(const double min, const double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1.0, 1.0), random_double(-1.0, 1.0), 0);
        if (p.length_squared() < 1.0)
            return p;
    }
}

vec3 random_unit_vector() {
    while (true) {
        auto p     = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1.0) {
            return p / std::sqrt(lensq);
        }
    }
}

vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    return -on_unit_sphere;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2.0 * dot(v, n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, const double eta_i_over_eta_t) {
    auto cos_theta      = std::min(dot(-uv, n), 1.0);
    vec3 r_out_perp     = eta_i_over_eta_t * (uv + cos_theta * n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
