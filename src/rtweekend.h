#pragma once

#ifndef INCLUDE_RTWEEKEND_H
#define INCLUDE_RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    static std::mt19937 engine{std::random_device{}()};
    static std::uniform_real_distribution<double> dist{0.0, 1.0};
    // Returns a random real in [0,1).
    return dist(engine);
}

inline double random_double(const double min, const double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif // INCLUDE_RTWEEKEND_H
