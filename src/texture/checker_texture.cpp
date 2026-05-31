#include "checker_texture.h"

#include "solid_color.h"

checker_texture::checker_texture(
    double scale, const std::shared_ptr<texture>& even, const std::shared_ptr<texture>& odd)
    : inv_scale(1.0 / scale), even(even), odd(odd) {}

checker_texture::checker_texture(double scale, const color& c1, const color& c2)
    : checker_texture(scale, std::make_shared<solid_color>(c1), std::make_shared<solid_color>(c2)) {}

color checker_texture::value(double u, double v, const point3& p) const {
    const int x_int = int(std::floor(inv_scale * p.x()));
    const int y_int = int(std::floor(inv_scale * p.y()));
    const int z_int = int(std::floor(inv_scale * p.z()));

    const bool is_even = (x_int + y_int + z_int) % 2 == 0;
    
    return is_even ? even->value(u, v, p) : odd->value(u, v, p);
}
