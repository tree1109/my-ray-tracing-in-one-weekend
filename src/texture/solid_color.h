#pragma once

#ifndef INCLUDE_SOLID_COLOR_H
#define INCLUDE_SOLID_COLOR_H

#include "texture.h"

class solid_color final : public texture {
public:
    solid_color(const color& albedo);
    solid_color(double red, double green, double blue);

    color value(double u, double v, const point3& p) const override;

private:
    color albedo;
};


#endif // INCLUDE_SOLID_COLOR_H
