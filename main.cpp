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
    unsigned int w,h;
    auto image = decode("../in.png", w, h);
    vector<unsigned char> image2,image3;
    copy(image.begin(), image.end(), back_inserter(image2));
    copy(image.begin(), image.end(), back_inserter(image3));

    // Un comment if you want to check buffer content
    //encode("../out.png", image, w, h);
    Blue("../b.png",image,w,h);
    Green("../g.png",image2,w,h);
    Red("../r.png",image3,w,h);
    return 0;
}
