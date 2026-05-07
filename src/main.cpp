#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

// PPM Viewer: https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html

namespace {
    color lerp_color(const color& a, const color& b, const double t) {
        return (1.0 - t) * a + t * b;
    }

    color ray_color(const ray& r, const hittable& world) {
        hit_record record;
        if (world.hit(r, interval(0.0, infinity), record)) {
            return 0.5 * (record.normal + color(1.0, 1.0, 1.0));
        }

        vec3 unit_direction = unit_vector(r.direction());
        const double a      = 0.5 * (unit_direction.y() + 1.0);
        return lerp_color(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), a);
    }
} // namespace

int main() {
    // Image.
    const double aspect_ratio = 16.0 / 9.0;
    const int image_height    = 400;
    // Calculate the image height, and ensure that it's at least 1.
    const int image_width     = std::max(int(image_height * aspect_ratio), 1);
    const int max_color_value = 255;

    // World.
    hittable_list world;
    {
        world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5));
        world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0));
    }

    // Camera.
    const double image_aspect_ratio = double(image_width) / image_height;
    const double viewport_height    = 2.0;
    const double viewport_width     = viewport_height * image_aspect_ratio;
    const double focal_length       = 1.0;
    const auto camera_center        = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    const auto viewport_u = vec3(viewport_width, 0, 0);
    const auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    const auto pixel_delta_u = viewport_u / image_width;
    const auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    const auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    const auto pixel00_loc         = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render.
    {
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n";
        std::cout << max_color_value << "\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                const auto pixel_center  = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                const auto ray_direction = pixel_center - camera_center;
                const ray r(camera_center, ray_direction);

                const color pixel_color = ray_color(r, world);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }
}
