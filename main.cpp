#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <string_view>
#include "lodepng.h"
#include "includes.h"
#include "Filter.h"


using namespace std;





int main()
{
    unsigned int w,w1,w2;
    unsigned int h,h1,h2;
    auto image = decode("../in.png", w, h);
    auto image2 = decode("../in.png", w1, h1);
    auto image3 = decode("../in.png", w2, h2);
    // Un comment if you want to check buffer content
    //encode("../out.png", image, w, h);
    Blue("../blue.png",image,w,h);
    Green("../green.png",image2,w1,h1);
    Red("../red.png",image3,w2,h2);
    return 0;
}
