#include "core.hpp"

int main()
{
    Image img;
    img.load("sample.png");
    negativeFilter(img);
    img.save("negative_sample.png");
    return 0;
}