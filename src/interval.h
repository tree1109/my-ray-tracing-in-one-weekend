#pragma once

#ifndef INCLUDE_INTERVAL_H
#define INCLUDE_INTERVAL_H
#include "rtweekend.h"

class interval {
public:
    double min;
    double max;

    // Default interval is empty.
    interval() : min(+infinity), max(-infinity) {}

    interval(const double min, const double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(const double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(const double x) const {
        return min < x && x < max;
    }

    static const interval empty, universe;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, infinity);

#endif // INCLUDE_INTERVAL_H
