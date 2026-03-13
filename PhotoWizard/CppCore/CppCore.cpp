//
//  CppCore.cpp
//  CppCore
//
//  Created by Даниил Буценин on 13.03.2026.
//

#include "CppCore.hpp"

/// @brief clamp value between possible values of type
/// @param value value to clamp
/// @return clamped uint8_t value (if more than 255, returns 255, if below 0, returns 0)
inline uint8_t clamp(double value)
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
/// @param pixel_array array of r,g,b from swift image
/// @return returns true if the filter was successfully applied and false if an error occurred.
bool negativeFilter(std::vector<uint8_t>& pixel_array)
{
    if(pixel_array.empty())
    {
        return false;
    }

    for(size_t index = 0; index < pixel_array.size() - 1; index++)
    {
        pixel_array[index] = 255 - pixel_array[index];
    }
    return true;
}

/// @brief apply brightness filter on image
/// @param pixel_array array of r,g,b from swift image
/// @param ratio ratio of brightness between -1.0 and 1.0
/// @param callBack a function that returns an array to swift at shutdown
void brightnessFilter(std::vector<uint8_t>& pixel_array, double ratio, std::function<void(std::vector<uint8_t>&)> callBack)
{
    if(pixel_array.empty())
    {
        return;
    }

    if(ratio > 1.0 || ratio < -1.0)
    {
        return;
    }

    double factor = 255 * ratio;

    for(size_t index = 0; index < pixel_array.size() - 1; index++)
    {
        pixel_array[index] = clamp(pixel_array[index] + factor);
    }
    callBack(pixel_array);

}

/// @brief apply contrast filter on image
/// @param pixel_array array of r,g,b from swift image
/// @param ratio ration of contrast between 0.0 and 3.0 (equal to 0.0 goes neutral (128, 128, 128) color, less than 0.0 goes negative)
/// @return returns true if the filter was successfully applied and false if an error occurred.
bool contrastFilter(std::vector<uint8_t>& pixel_array, double ratio)
{
    if(pixel_array.empty())
    {
        return false;
    }

    if(ratio > 3.0 || ratio < 0.0)
    {
        return false;
    }

    for(size_t index = 0; index < pixel_array.size() - 1; index++)
    {
        pixel_array[index] = clamp((pixel_array[index] - 128) * ratio + 128);
    }
    return true;
}

/// @brief apply exposure filter on image
/// @param pixel_array loaded pixel_array class
/// @param ratio ration of exposure goes from -2.0 to 2.0 (where 0.0 is default pic)
/// @return returns true if the filter was successfully applied and false if an error occurred.
bool exposureFilter(std::vector<uint8_t>& pixel_array, double ratio)
{
    if(pixel_array.empty())
    {
        return false;
    }

    if(ratio > 2.0 || ratio < -2.0)
    {
        return false;
    }

    double factor = std::pow(2, ratio);

    for(size_t index = 0; index < pixel_array.size() - 1; index++)
    {
        pixel_array[index] = clamp(pixel_array[index] * factor);
    }
    return true;
}

