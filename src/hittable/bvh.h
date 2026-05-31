#pragma once

#ifndef INCLUDE_BVH_H
#define INCLUDE_BVH_H

#include "hittable.h"
#include "hittable_list.h"

class bvh_node final : public hittable
{
public:
    bvh_node(hittable_list list);
    bvh_node(std::vector<std::shared_ptr<hittable>>& objects, size_t start, size_t end);

    bool hit(const ray& r, const interval& ray_t, hit_record& rec) const override;

    aabb bounding_box() const override;

private:
    static bool box_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b, int axis_index);
    static bool box_x_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b);
    static bool box_y_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b);
    static bool box_z_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b);

private:
    std::shared_ptr<hittable> left;
    std::shared_ptr<hittable> right;
    aabb bbox;
};

#endif //INCLUDE_BVH_H
