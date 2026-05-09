#include "utility.h"

#include "common_define.h"
#include <random>

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

double random_double() {
    static std::mt19937 engine{std::random_device{}()};
    static std::uniform_real_distribution<double> dist{0.0, 1.0};
    // Returns a random real in [0,1).
    return dist(engine);
}

double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}
