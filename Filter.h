//
// Created by Usuario on 12/2/2019.
//
#ifndef PC4_FILTER_H
#define PC4_FILTER_H
#include "includes.h"


void filter(const string_view& myfile,vector<unsigned char>& image, const unsigned w, unsigned a, unsigned b, const int& p,
           const int& m) {

    for (size_t i = a; i < b; i++) {
        for (size_t j = 0; j < w * 4; j += 4) {
            image[i * w * 4 + j + p]=0;
            image[i * w * 4 + j + m]=0;
        }
    }
    encode(myfile.data(), image, w, b);
}
void Red(const string_view& myfile, vector<unsigned char>& image, const unsigned & w,const unsigned &h){
    int p=2,m=1;
    thread t[4];
    int c=0;
    for(auto &u:t){
        u=thread(filter,myfile,ref(image), w, h*c/4, h*(c+1)/4,p,m);
        c++;
    }
    for(auto & u : t){
        u.join();
    }
}

void Blue(const string_view& myfile, vector<unsigned char>& image, const unsigned& w, const unsigned& h){
    int p=0,m=1;
    thread t[4];
    int c=0;
    for(auto &u:t){
        u=thread(filter,myfile,ref(image), w, h*c/4, h*(c+1)/4,p,m);
        c++;
    }
    for(auto & u : t){
        u.join();
    }
}

void Green(const string_view& myfile, vector<unsigned char>& image, const unsigned& w,const unsigned& h){
    int p=0,m=2;
    thread t[4];
    int c=0;
    for(auto &u:t){
        u=thread(filter,myfile,ref(image), w, h*c/4, h*(c+1)/4,p,m);
        c++;
    }
    for(auto & u : t){
        u.join();
    }
}








#endif //PC4_FILTER_H
