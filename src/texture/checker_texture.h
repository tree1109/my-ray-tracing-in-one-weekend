#pragma once

#ifndef INCLUDE_CHECKER_TEXTURE_H
#define INCLUDE_CHECKER_TEXTURE_H
#include "texture.h"

class checker_texture final : public texture {
public:
    checker_texture(double scale, const std::shared_ptr<texture>& even, const std::shared_ptr<texture>& odd);
    checker_texture(double scale, const color& c1, const color& c2);

    color value(double u, double v, const point3& p) const override;

private:
    double inv_scale;
    std::shared_ptr<texture> even;
    std::shared_ptr<texture> odd;
};

#endif // INCLUDE_CHECKER_TEXTURE_H
