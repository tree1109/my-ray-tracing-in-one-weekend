#pragma once

#ifndef INCLUDE_VEC3_H
#define INCLUDE_VEC3_H

class vec3 {
public:
    vec3() : e{0, 0, 0} {}
    vec3(const double x, const double y, const double z) : e{x, y, z} {}

    [[nodiscard]] const double& x() const { return e[0]; }
    [[nodiscard]] const double& y() const { return e[1]; }
    [[nodiscard]] const double& z() const { return e[2]; }

    [[nodiscard]] const double& r() const { return e[0]; }
    [[nodiscard]] const double& g() const { return e[1]; }
    [[nodiscard]] const double& b() const { return e[2]; }

    vec3 operator-() const {
        return vec3{-e[0], -e[1], -e[2]};
    }

    double operator[](const int i) const {
        return e[i];
    }

    double& operator[](const int i) {
        return e[i];
    }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const vec3& v) {
        e[0] *= v.e[0];
        e[1] *= v.e[1];
        e[2] *= v.e[2];
        return *this;
    }

    [[nodiscard]] double length() const {
        return std::sqrt(length_squared());
    }

    [[nodiscard]] double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(const double min, const double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

public:
    double e[3]{};
};

using point3 = vec3;

// Vector utility functions.

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(const double t, const vec3& v) {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator*(const vec3& v, const double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, const double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return {u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1.0) {
            return p / std::sqrt(lensq);
        }
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

#endif // INCLUDE_VEC3_H
