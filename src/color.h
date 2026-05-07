#pragma once

#ifndef INCLUDE_COLOR_H
#define INCLUDE_COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    const double r = pixel_color.x();
    const double g = pixel_color.y();
    const double b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    static const interval intensity(0.000, 0.999);
    const int rByte = int(256 * intensity.clamp(r));
    const int gByte = int(256 * intensity.clamp(g));
    const int bByte = int(256 * intensity.clamp(b));

    // Write out the pixel color components.
    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}


#endif // INCLUDE_COLOR_H
