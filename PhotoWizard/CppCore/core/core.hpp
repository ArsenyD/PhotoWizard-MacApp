#pragma once

#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>

#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"

struct Pixel
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class Image
{
public:
    Image() = default;

    std::vector<Pixel>& getData()
    {
        return m_data;
    }

    bool load(const std::string& filename);
    bool save(const std::string& filename) const;

    int getWidth() const;
    int getHeight() const;

private:
    std::vector<Pixel> m_data;
    int m_width = 0, m_height = 0, m_channels = 0;

};

uint8_t clamp(double value);

bool negativeFilter(Image& img);
bool brightnessFilter(Image& img, double ratio);
bool contrastFilter(Image& img, double ratio);
bool exposureFilter(Image& img, double ratio);