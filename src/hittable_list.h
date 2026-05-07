#pragma once

#ifndef INCLUDE_HITTABLE_LIST_H
#define INCLUDE_HITTABLE_LIST_H

#include "hittable.h"
#include "rtweekend.h"
#include <vector>

class hittable_list final : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list() = default;
    hittable_list(std::shared_ptr<hittable> object) {
        add(object);
    }

    void clear() {
        objects.clear();
    }

    void add(std::shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, const double ray_t_min, const double ray_t_max, hit_record& record) const override {
        hit_record temp_record;
        bool hit_anything     = false;
        double closest_so_far = ray_t_max;

        for (const auto& object : objects) {
            if (object->hit(r, ray_t_min, closest_so_far, temp_record)) {
                hit_anything   = true;
                closest_so_far = temp_record.t;
                record         = temp_record;
            }
        }

        return hit_anything;
    }
};

#endif // INCLUDE_HITTABLE_LIST_H
