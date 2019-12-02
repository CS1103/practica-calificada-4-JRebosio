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
    unsigned int w,h,cw,ch;
    auto image = decode("../in.png", w, h);
    vector<unsigned char> image2,image3,dados2, dados3,imagemove;
    auto dados = decode("../dados.png", cw, ch);
    copy(dados.begin(), dados.end(), back_inserter(dados2));
    copy(dados.begin(), dados.end(), back_inserter(dados3));
    copy(image.begin(), image.end(), back_inserter(image2));
    copy(image.begin(), image.end(), back_inserter(image3));
    copy(image.begin(), image.end(), back_inserter(imagemove));

    // Un comment if you want to check buffer content
    //encode("../out.png", image, w, h);
    Green("../dadosgreen.jpg",dados2,cw,ch);
    Red("../dadosred.jpg",dados3,cw,ch);
    Blue("../dadosblue.jpg",dados,cw,ch);
    Blue("../b.png",image,w,h);
    Green("../g.png",image2,w,h);
    Red("../r.png",image3,w,h);
    mover(imagemove,h,w);
    return 0;
}
