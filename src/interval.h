#pragma once

#ifndef INCLUDE_INTERVAL_H
#define INCLUDE_INTERVAL_H

class interval {
public:
    // Default interval is empty.
    interval();
    interval(double min, double max);

    double size() const;

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;

    static const interval& empty();

    static const interval& universe();

public:
    double min;
    double max;
};

#endif // INCLUDE_INTERVAL_H
