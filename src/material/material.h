#pragma once

#ifndef INCLUDE_MATERIAL_H
#define INCLUDE_MATERIAL_H

#include "texture/texture.h"

class material {
public:
    virtual ~material() = default;

public:
    virtual bool scatter(const ray& r_in, const hit_record& record, color& attenuation, ray& scattered) const {
        return false;
    }
};


#endif // INCLUDE_MATERIAL_H
