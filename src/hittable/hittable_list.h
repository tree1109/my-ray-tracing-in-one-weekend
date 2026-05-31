#pragma once

#ifndef INCLUDE_HITTABLE_LIST_H
#define INCLUDE_HITTABLE_LIST_H

#include "hittable.h"
#include <vector>

class hittable_list final : public hittable {
public:
    hittable_list() = default;
    hittable_list(const std::shared_ptr<hittable>& object);

    void clear();

    void add(const std::shared_ptr<hittable>& object);

    bool hit(const ray& r, const interval& ray_t, hit_record& record) const override;

    aabb bounding_box() const override;

public:
    std::vector<std::shared_ptr<hittable>> objects;

private:
    aabb bbox;
};

#endif // INCLUDE_HITTABLE_LIST_H
