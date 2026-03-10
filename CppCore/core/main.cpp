#include "core.hpp"

int main()
{
    Image img;
    img.load("sample.png");
    if(contrastFilter(img, 0.0))
    {
        img.save("contrast_sample.png");
    }
    else
    {
        std::cerr << "Error while applying filter\n";
    }
    return 0;
}