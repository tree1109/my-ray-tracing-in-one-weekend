#pragma once

#ifndef INCLUDE_COLOR_H
#define INCLUDE_COLOR_H


#include "interval.h"
#include "vec3.h"
#include "std_image_write.h"

using color = vec3;

inline double linear_to_gamma(const double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }
    return 0;
}

class image {
public:
    int width;
    int height;
    std::vector<color> pixels;

    image(const int width, const int height) : width(width), height(height), pixels(width * height) {}

    void write_color(const int x, const int y, const color& pixel_color) {
        pixels[y * width + x] = pixel_color;
    }
};

inline image linear_image_to_gamma_image(const image& linear_image) {
    image gamma_image(linear_image.width, linear_image.height);
    for (int i = 0; i < linear_image.pixels.size(); ++i) {
        const color& linear_pixel = linear_image.pixels[i];

        double r = linear_pixel.x();
        double g = linear_pixel.y();
        double b = linear_pixel.z();

        // Apply a linear to gamma transform for gamma 2
        r = linear_to_gamma(r);
        g = linear_to_gamma(g);
        b = linear_to_gamma(b);

        color& gamma_pixel = gamma_image.pixels[i];
        gamma_pixel        = color(r, g, b);
    }

    return gamma_image;
}

inline void write_image_ppm(std::ostream& out, const image& image) {
    std::cout << "P3\n" << image.width << ' ' << image.height << "\n255\n";

    for (int j = 0; j < image.height; j++) {
        for (int i = 0; i < image.width; i++) {
            const color& pixel_color = image.pixels[j * image.width + i];

            double r = pixel_color.x();
            double g = pixel_color.y();
            double b = pixel_color.z();

            // Translate the [0,1] component values to the byte range [0,255].
            static const interval intensity(0.000, 0.999);
            const int rByte = int(256 * intensity.clamp(r));
            const int gByte = int(256 * intensity.clamp(g));
            const int bByte = int(256 * intensity.clamp(b));

            // Write out the pixel color components.
            out << rByte << ' ' << gByte << ' ' << bByte << '\n';
        }
    }
}

inline void write_image_png(const std::string& file_name, const image& image) {
    const int channels = 3;
    std::vector<unsigned char> png_buffer(image.width * image.height * channels);

    for (int j = 0; j < image.height; j++) {
        for (int i = 0; i < image.width; i++) {
            const int pixel_index = j * image.width + i;

            const color& pixel_color = image.pixels[pixel_index];
            double r = pixel_color.x();
            double g = pixel_color.y();
            double b = pixel_color.z();

            // Translate the [0,1] component values to the byte range [0,255].
            static const interval intensity(0.000, 0.999);
            const unsigned char rByte = unsigned char(256 * intensity.clamp(r));
            const unsigned char gByte = unsigned char(256 * intensity.clamp(g));
            const unsigned char bByte = unsigned char(256 * intensity.clamp(b));

            png_buffer[pixel_index * channels + 0] = rByte;
            png_buffer[pixel_index * channels + 1] = gByte;
            png_buffer[pixel_index * channels + 2] = bByte;
        }
    }

    stbi_write_png(file_name.c_str(), image.width, image.height, channels, png_buffer.data(), image.width * channels);
}

#endif // INCLUDE_COLOR_H
