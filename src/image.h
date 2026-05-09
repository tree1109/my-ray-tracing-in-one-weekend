#pragma once

#ifndef INLCUDE_IMAGE_H
#define INCLUDE_IMAGE_H

#include <vector>
#include <iostream>
#include <string>
#include "color.h"

class image {
public:
    image(int width, int height);

    void write_color(int x, int y, const color& pixel_color);
    
public:
    int width;
    int height;
    std::vector<color> pixels;
};

image linear_image_to_gamma_image(const image& linear_image);

void write_image_ppm(std::ostream& out, const image& image);

void write_image_png(const std::string& file_name, const image& image);

#endif // INCLUDE_IMAGE_H
