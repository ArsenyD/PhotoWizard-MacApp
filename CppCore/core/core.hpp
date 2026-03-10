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

void negativeFilter(Image& img)
{
    for(size_t index = 0; index < img.getHeight() * img.getWidth(); index++)
    {
        img.getData()[index].red = 255 - img.getData()[index].red;
        img.getData()[index].green = 255 - img.getData()[index].green;
        img.getData()[index].blue = 255 - img.getData()[index].blue;
    }
}