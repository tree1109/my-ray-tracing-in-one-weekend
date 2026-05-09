#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"
#include "material.h"

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

// PPM Viewer: https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html

namespace {
    void scene_1(camera& cam, hittable_list& world) {
        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
        auto material_left   = make_shared<dielectric>(1.5);
        auto material_bubble = make_shared<dielectric>(1.0 / 1.5);
        auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

        world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
        world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
        world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
        world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width  = 900;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;
    }

    void scene_2(camera& cam, hittable_list& world) {
        auto R = std::cos(pi/4);

        auto material_left  = make_shared<lambertian>(color(0,0,1));
        auto material_right = make_shared<lambertian>(color(1,0,0));

        world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
        world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));

        cam.aspect_ratio      = 16.0 / 9.0;
        cam.image_width       = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth         = 50;

        cam.vfov = 90;
    }

}

int main() {
    hittable_list world;
    camera cam;

    // scene_1(cam, world);
    scene_2(cam, world);

    cam.render(world);
}
