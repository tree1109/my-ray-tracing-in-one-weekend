#include "color.h"

#include <cmath>

double linear_to_gamma(double linear_component) {
    if (linear_component <= 0) {
        return 0;
    }
    return std::sqrt(linear_component);
}