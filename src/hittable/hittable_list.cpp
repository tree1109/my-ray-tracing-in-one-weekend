#include "hittable_list.h"

hittable_list::hittable_list(const std::shared_ptr<hittable>& object) {
    add(object);
}

void hittable_list::clear() {
    objects.clear();
}

void hittable_list::add(const std::shared_ptr<hittable>& object) {
    objects.push_back(object);
    bbox = aabb(bbox, object->bounding_box());
}

bool hittable_list::hit(const ray& r, const interval& ray_t, hit_record& record) const {
    hit_record temp_record;
    bool hit_anything     = false;
    double closest_so_far = ray_t.max;

    for (const auto& object : objects) {
        if (object->hit(r, interval(ray_t.min, closest_so_far), temp_record)) {
            hit_anything   = true;
            closest_so_far = temp_record.t;
            record         = temp_record;
        }
    }

    return hit_anything;
}

aabb hittable_list::bounding_box() const {
    return bbox;
}