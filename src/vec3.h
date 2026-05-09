#pragma once

#ifndef INCLUDE_VEC3_H
#define INCLUDE_VEC3_H

#include <iostream>

class vec3 {
public:
    vec3();
    vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;

    double operator[](int i) const;

    double& operator[](int i);

    vec3& operator+=(const vec3& v);

    vec3& operator*=(const vec3& v);

    double length() const;

    double length_squared() const;

    bool near_zero() const;

    static vec3 random();

    static vec3 random(double min, double max);

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

inline vec3 operator*(double t, const vec3& v) {
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
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

vec3 random_in_unit_disk();

vec3 random_unit_vector();

vec3 random_on_hemisphere(const vec3& normal);

vec3 reflect(const vec3& v, const vec3& n);

vec3 refract(const vec3& uv, const vec3& n, const double eta_i_over_eta_t);

#endif // INCLUDE_VEC3_H
