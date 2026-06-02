#ifndef INCLUDE_IMAGE_TEXTURE_H
#define INCLUDE_IMAGE_TEXTURE_H

#include "stb/rtw_stb_image.h"
#include "texture.h"

class image_texture final : public texture {
public:
    image_texture(const char* filename);

    color value(double u, double v, const point3& p) const override;

private:
    rtw_image image;
};


#endif // INCLUDE_IMAGE_TEXTURE_H
