//
// Created by Usuario on 12/2/2019.
//
#ifndef PC4_FILTER_H
#define PC4_FILTER_H
#include "includes.h"
#define ang M_PI/4
#define mx 100000
#define mn 0

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


void mover(vector<unsigned char>& image, unsigned& h, unsigned& w) {
    map<pair<int, int>, array<unsigned char, 4>> img;
    map<pair<int, int>, array<unsigned char, 4>> ir ;
    vector<unsigned char> move;
    int mini=mx,minj=mx,maxi=mn,maxj=mn;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w * 4; j += 4) {
            unsigned char r = image[i * w * 4 + j + 0]; // Red component
            unsigned char g = image[i * w * 4 + j + 1]; // Green component
            unsigned char b = image[i * w * 4 + j + 2]; // Blue component
            unsigned char a = image[i * w * 4 + j + 3]; // Alpha component
            int temp = j / 4;
            img[{i, temp}] = {{r, g, b, a}};
            int jmove = (int) (double(temp) * cos(ang) - double(i) * sin(ang));
            int imove = (int) (double(temp) * sin(ang) + double(i) * sin(ang));
            ir[{imove, jmove}] = img[{i, temp}];
            mini = min(imove, mini);
            maxi = max(imove, maxi);
            minj = min(jmove, minj);
            maxj = max(jmove, maxj);
        }
    }
    int rangemovej=maxj-minj +1;
    int rangemovei= maxi-mini+1;
    for (int i = mini; i <=maxi; i++)
        for (int j = minj; j <=maxj; j++)
        {
            if (ir.find({i,j})!=ir.end())
                for(const auto& s: ir[{i,j}])
                    move.emplace_back(s);
            else
                for(const auto& s: ir[{i,j}])
                    move.emplace_back(0);
        }
    encode("../movipng", move, rangemovej, rangemovei);
}









#endif //PC4_FILTER_H
