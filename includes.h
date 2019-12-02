//
// Created by Usuario on 12/2/2019.
//

#ifndef PC4_INCLUDES_H
#define PC4_INCLUDES_H

#include <thread>
#include <iostream>
#include <vector>
#include <string_view>
#include "lodepng.h"

using namespace std;
std::vector<unsigned char> decode(string_view filename, unsigned int& width, unsigned int& height) {

    std::vector<unsigned char> result;
    unsigned error = lodepng::decode(result, width, height, filename.data());
    if (error) {
        std::cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
    return result;
}

void encode(string_view filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
    unsigned error = lodepng::encode(filename.data(), image, width, height);
    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}




#endif //PC4_INCLUDES_H