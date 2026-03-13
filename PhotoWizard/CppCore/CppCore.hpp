//
//  CppCore.hpp
//  CppCore
//
//  Created by Даниил Буценин on 13.03.2026.
//

#ifndef CppCore_
#define CppCore_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <functional>

uint8_t clamp(double value);

bool negativeFilter(std::vector<uint8_t>& pixel_array);
void brightnessFilter(std::vector<uint8_t>& pixel_array, double ratio, std::function<void(std::vector<uint8_t>&)> callBack);
bool contrastFilter(std::vector<uint8_t>& pixel_array, double ratio);
bool exposureFilter(std::vector<uint8_t>& pixel_array, double ratio);


#pragma GCC visibility pop
#endif
