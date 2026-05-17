#include "camera.h"

#include "common_define.h"
#include "utility.h"
#include "hittable/hittable.h"
#include "material/material.h"
#include <deque>
#include <format>
#include <future>

image camera::render(const hittable& world) {
    initialize();

    image image(image_width, image_height);

    // Single thread
    if (false) {
        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r       = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                pixel_color = pixel_samples_scale * pixel_color;

                image.write_color(i, j, pixel_color);
            }
        }

        std::clog << "\rDone.                                                                           \n";
    }
    // Multi thread
    else {
        auto write_colors = [&](const int x, const int y, const int w, const int h) {
            for (int j = y; j < h; j++) {
                for (int i = x; i < w; i++) {
                    color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r       = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    pixel_color = pixel_samples_scale * pixel_color;

                    image.write_color(i, j, pixel_color);
                }
            }
        };

        constexpr int block_size = 16;
        const int num_threads = std::thread::hardware_concurrency();
        std::vector<std::vector<std::function<void()>>> threads_jobs(num_threads);
        std::clog << "\rThread num: " << num_threads << ' ' << std::flush;

        const int total_blocks = (image_width + block_size - 1) / block_size * (image_height + block_size - 1) / block_size;
        for (auto& jobs : threads_jobs) {
            jobs.reserve((total_blocks + num_threads - 1) / num_threads);
        }
        std::clog << "\rBlocks total: " << total_blocks << ' ' << std::flush;

        int current_block = 0;
        for (int j = 0; j < image_height; j+=block_size) {
            for (int i = 0; i < image_width; i+=block_size) {
                const int x = i;
                const int y = j;
                const int w = std::min(i + block_size, image_width);
                const int h = std::min(j + block_size, image_height);

                auto job = std::bind(write_colors, x, y, w, h);
                threads_jobs.at(current_block % num_threads).push_back(std::move(job));

                ++current_block;
            }
        }

        const auto start_time = std::chrono::steady_clock::now();

        std::vector<std::thread> threads;
        threads.reserve(num_threads);
        int current_thread = 0;
        for (const auto& jobs : threads_jobs) {
            auto thread = std::thread{[&jobs, current_thread] {
                const int total_jobs = (int)jobs.size();
                int current_job = 0;
                for (const auto& job : jobs) {
                    std::clog << std::format("\rThread {} with remaining job {} ", current_thread, total_jobs - current_job) << std::flush;
                    job();
                    ++current_job;
                }
            }};
            threads.push_back(std::move(thread));
            ++current_thread;
        }

        current_thread = 0;
        const int total_threads = (int)threads.size();
        for (auto& thread : threads) {
            std::clog << "\rThread remaining: " << (total_threads - current_thread) << ' ' << std::flush;
            thread.join();

            ++current_thread;
        }

        const auto elapsed_time = std::chrono::steady_clock::now() - start_time;
        const auto time = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed_time);
        std::clog << "\rDone by " << time.count() << " second.                                             \n";
    }

    return image;
}

void camera::initialize() {
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    // Determine viewport dimensions.
    auto theta           = degrees_to_radians(vfov);
    auto h               = std::tan(theta / 2.0);
    auto viewport_height = 2.0 * h * focus_dist;
    auto viewport_width  = viewport_height * (double(image_width) / image_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = viewport_width * u; // Vector across viewport horizontal edge
    vec3 viewport_v = viewport_height * -v; // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    pixel00_loc              = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors.
    auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u      = u * defocus_radius;
    defocus_disk_v      = v * defocus_radius;
}

ray camera::get_ray(const int i, const int j) const {
    // Construct a camera ray originating from the defocus disk and directed at a randomly
    // sampled point around the pixel location i, j.

    auto offset       = sample_square();
    auto pixel_sample = pixel00_loc
                        + ((i + offset.x()) * pixel_delta_u)
                        + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin    = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;
    auto ray_time = random_double();

    return ray(ray_origin, ray_direction, ray_time);
}

vec3 camera::sample_square() const {
    // Returns the vector to a random point in the [-0.5,-0.5]-[+0.5,+0.5] unit square.
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

point3 camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

color camera::ray_color(const ray& r, const int depth, const hittable& world) const {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    hit_record record;

    if (world.hit(r, interval(0.001, infinity), record)) {
        ray scattered;
        color attenuation;
        if (record.mat->scatter(r, record, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1, world);
        }
        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    const double a      = 0.5 * (unit_direction.y() + 1.0);
    const color color_a = color(1.0, 1.0, 1.0);
    const color color_b = color(0.5, 0.7, 1.0);
    return (1.0 - a) * color_a + a * color_b;
}
