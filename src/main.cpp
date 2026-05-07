#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

// PPM Viewer: https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5));
    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}
