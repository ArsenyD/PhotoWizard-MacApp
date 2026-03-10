#include "core.hpp"

int main()
{
    Image img;
    img.load("sample.png");
    exposureFilter(img, 0.0);
    contrastFilter(img, 0.9);
    brightnessFilter(img, 0.0);

    img.save("combined_filter_sample.png");
    return 0;
}