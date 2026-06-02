#include "camera.h"
#include "hittable/bvh.h"
#include "hittable/hittable.h"
#include "hittable/hittable_list.h"
#include "material/dielectric.h"
#include "material/lambertian.h"
#include "material/material.h"
#include "material/metal.h"
#include "texture/checker_texture.h"
#include "utility.h"
#include "texture/image_texture.h"
#include <hittable/sphere.h>

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

// PPM Viewer: https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html

namespace {
    void scene_1(camera& cam, hittable_list& world) {
        auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left   = std::make_shared<dielectric>(1.50);
        auto material_bubble = std::make_shared<dielectric>(1.00 / 1.50);
        auto material_right  = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

        world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
        world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

        cam.aspect_ratio      = 16.0 / 9.0;
        cam.image_width       = 900;
        cam.samples_per_pixel = 100;
        cam.max_depth         = 50;

        cam.vfov     = 20;
        cam.lookfrom = point3(-2, 2, 1);
        cam.lookat   = point3(0, 0, -1);
        cam.vup      = vec3(0, 1, 0);

        cam.defocus_angle = 10.0;
        cam.focus_dist    = 3.4;
    }

    void scene_bouncing_spheres(camera& cam, hittable_list& world) {
        auto checker_tex = std::make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
        auto ground_mat  = std::make_shared<lambertian>(checker_tex);

        world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground_mat));

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                auto choose_mat = random_double();
                point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

                if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                    std::shared_ptr<material> sphere_material;

                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo     = color::random() * color::random();
                        sphere_material = std::make_shared<lambertian>(albedo);
                        auto center2    = center + vec3(0, random_double(0, 0.5), 0);
                        world.add(std::make_shared<sphere>(center, center2, 0.2, sphere_material));
                    } else if (choose_mat < 0.95) {
                        // metal
                        auto albedo     = color::random(0.5, 1);
                        auto fuzz       = random_double(0, 0.5);
                        sphere_material = std::make_shared<metal>(albedo, fuzz);
                        world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                    } else {
                        // glass
                        sphere_material = std::make_shared<dielectric>(1.5);
                        world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                    }
                }
            }
        }

        auto material1 = std::make_shared<dielectric>(1.5);
        world.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

        auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
        world.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

        auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
        world.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

        world = hittable_list(std::make_shared<bvh_node>(world));

        cam.aspect_ratio = 16.0 / 9.0;
        // cam.image_width       = 1200;
        cam.image_width = 400;
        // cam.samples_per_pixel = 500;
        cam.samples_per_pixel = 100;
        // cam.samples_per_pixel = 10;
        cam.max_depth = 50;

        cam.vfov     = 20;
        cam.lookfrom = point3(13, 2, 3);
        cam.lookat   = point3(0, 0, 0);
        cam.vup      = vec3(0, 1, 0);

        cam.defocus_angle = 0.6;
        cam.focus_dist    = 10.0;
    }

    void scene_checkered_spheres(camera& cam, hittable_list& world) {
        auto checker = std::make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));

        world.add(std::make_shared<sphere>(point3(0,-10, 0), 10, std::make_shared<lambertian>(checker)));
        world.add(std::make_shared<sphere>(point3(0, 10, 0), 10, std::make_shared<lambertian>(checker)));

        cam.aspect_ratio      = 16.0 / 9.0;
        cam.image_width       = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth         = 50;

        cam.vfov     = 20;
        cam.lookfrom = point3(13,2,3);
        cam.lookat   = point3(0,0,0);
        cam.vup      = vec3(0,1,0);

        cam.defocus_angle = 0;
    }

    void scene_earth(camera& cam, hittable_list& world) {
        auto earth_texture = std::make_shared<image_texture>("earthmap.jpg");
        auto earth_surface = std::make_shared<lambertian>(earth_texture);
        auto globe         = std::make_shared<sphere>(point3(0,0,0), 2, earth_surface);

        world.add(globe);

        cam.aspect_ratio      = 16.0 / 9.0;
        cam.image_width       = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth         = 50;

        cam.vfov     = 20;
        cam.lookfrom = point3(0,0,12);
        cam.lookat   = point3(0,0,0);
        cam.vup      = vec3(0,1,0);

        cam.defocus_angle = 0;
    }
} // namespace

int main() {

    hittable_list world;
    camera cam;

    // Scene.
    switch (3) {
        case 1: scene_bouncing_spheres(cam, world); break;
        case 2: scene_checkered_spheres(cam, world); break;
        case 3: scene_earth(cam, world); break;
        default: scene_1(cam, world); break;
    }

    // Render.
    auto render_image = cam.render(world);
    render_image      = linear_image_to_gamma_image(render_image);

    // Output image.
    const bool use_ppm_format = false;
    if (use_ppm_format) {
        write_image_ppm(std::cout, render_image);
    }
    else {
        write_image_png("output.png", render_image);
    }
}
