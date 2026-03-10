#include "core.hpp"

int main()
{
    Image img;
    img.load("sample.png");
    brightnessFilter(img, 0.3);
    contrastFilter(img, 1.2);
    exposureFilter(img, -0.5);

    img.save("combined_filter_sample.png");
    return 0;
}