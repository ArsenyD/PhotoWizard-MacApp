#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

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


    int getWidth() const
    {
        return m_width;
    }

    int getHeight() const
    {
        return m_height;
    }

    std::vector<Pixel>& getData()
    {
        return m_data;
    }

    /// @brief load and save img data into this class
    /// @param filename basic std::string C++ class
    /// @return returns true if the load was successfully completed and false if an error occurred.
    bool load(const std::string& filename)
    {
        stbi_uc* loaded_pic = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 3);

        if(!loaded_pic)
        {
            std::cerr << "Can't open file\n";
            return false;
        }
        m_data.reserve(m_height * m_width);

        for(size_t index = 0; index < static_cast<size_t>(m_width * m_height); index++)
        {
            Pixel pixel;
            pixel.red = loaded_pic[index * 3];
            pixel.green = loaded_pic[index * 3 + 1];
            pixel.blue = loaded_pic[index * 3 + 2];
            m_data.push_back(std::move(pixel));
        }

        stbi_image_free(loaded_pic);

        return true;
    }

    /// @brief save img data as new image with given filename
    /// @param filename new image fileneame
    /// @return returns true if the saving was successfully completed and false if an error occurred.
    bool save(const std::string& filename) const
    {
        if(m_data.empty())
        {
            return false;
        }
        if(!stbi_write_png(filename.c_str(), m_width, m_height, m_channels, reinterpret_cast<const uint8_t*>(m_data.data()), 0))
        {
            std::cerr << "Can't save file\n";
            return false;
        }
        return true;
    }

private:
    std::vector<Pixel> m_data;
    int m_width, m_height, m_channels;

};

/// @brief clamp value between possible values of type
/// @param value 
/// @return clamped uint8_t value (if more than 255, returns 255, if below 0, returns 0)
uint8_t clamp(double value)
{
    if(value > 255)
    {
        return 255;
    }
    else if(value < 0)
    {
        return 0;
    }
    else
    {
        return static_cast<uint8_t>(value);
    }
}

/// @brief apply negative filter on image
/// @param img loaded image class
/// @return returns true if the filter was successfully applied and false if an error occurred.
bool negativeFilter(Image& img)
{
    if(img.getData().empty())
    {
        return false;
    }

    for(size_t index = 0; index < static_cast<size_t>(img.getHeight() * img.getWidth()); index++)
    {
        img.getData()[index].red = 255 - img.getData()[index].red;
        img.getData()[index].green = 255 - img.getData()[index].green;
        img.getData()[index].blue = 255 - img.getData()[index].blue;
    }
    return true;
}

/// @brief apply brightness filter on image
/// @param img loaded image class
/// @param ratio ratio of brightness between -1.0 and 1.0
/// @return returns true if the filter was successfully applied and false if an error occurred.
bool brightnessFilter(Image& img, double ratio)
{
    if(img.getData().empty())
    {
        return false;
    }

    if(ratio > 1.0 || ratio < -1.0)
    {
        return false;
    }

    for(size_t index = 0; index < static_cast<size_t>(img.getHeight() * img.getWidth()); index++)
    {
        img.getData()[index].red = clamp(img.getData()[index].red + 255 * ratio);
        img.getData()[index].green = clamp(img.getData()[index].green + 255 * ratio);
        img.getData()[index].blue = clamp(img.getData()[index].blue + 255 * ratio);
    }
    return true;
}

/// @brief apply contrast filter on image
/// @param img loaded image class
/// @param ratio ration of contrast between -5.0 and 5.0 (equal to 0.0 goes neutral (128, 128, 128) color, less than 0.0 goes negative)
/// @return returns true if the filter was successfully applied and false if an error occurred.
bool contrastFilter(Image& img, double ratio)
{
    if(img.getData().empty())
    {
        return false;
    }

    if(ratio > 5.0 || ratio < -5.0)
    {
        return false;
    }

    for(size_t index = 0; index < static_cast<size_t>(img.getHeight() * img.getWidth()); index++)
    {
        img.getData()[index].red = clamp((img.getData()[index].red - 128) * ratio + 128);
        img.getData()[index].green = clamp((img.getData()[index].green - 128) * ratio + 128);
        img.getData()[index].blue = clamp((img.getData()[index].blue - 128) * ratio + 128);
    }
    return true;
}