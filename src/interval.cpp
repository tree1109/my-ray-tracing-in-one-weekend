#include "interval.h"

#include "common_define.h"
#include <algorithm>

interval::interval(): min(+infinity), max(-infinity) {}

interval::interval(double min, double max): min(min), max(max) {}

double interval::size() const {
    return max - min;
}

bool interval::contains(double x) const {
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const {
    return min < x && x < max;
}

double interval::clamp(double x) const {
    return std::clamp(x, min, max);
}

const interval& interval::empty() {
    static const interval empty(+infinity, -infinity);
    return empty;
}

const interval& interval::universe() {
    static const interval universe(-infinity, infinity);
    return universe;
}
