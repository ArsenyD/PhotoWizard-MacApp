#pragma once

#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>


uint8_t clamp(double value);

bool negativeFilter(std::vector<uint8_t>& pixel_array);
bool brightnessFilter(std::vector<uint8_t>& pixel_array, double ratio);
bool contrastFilter(std::vector<uint8_t>& pixel_array, double ratio);
bool exposureFilter(std::vector<uint8_t>& pixel_array, double ratio);
