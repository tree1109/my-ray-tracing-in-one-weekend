#pragma once

#ifndef INCLUDE_TEXTURE_H
#define INCLUDE_TEXTURE_H

#include "color.h"
#include "vec3.h"

class texture {
public:
    virtual ~texture() = default;

public:
    virtual color value(double u, double v, const point3& p) const = 0;
};


#endif // INCLUDE_TEXTURE_H
