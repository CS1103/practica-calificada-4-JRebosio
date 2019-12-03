//
// Created by Usuario on 12/2/2019.
//
#ifndef PC4_FILTER_H
#define PC4_FILTER_H
#include "includes.h"
map<pair<int, int>, array<unsigned char, 4>> img;


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


void mover(const string_view& myfile,vector<unsigned char>& image, const unsigned& w, unsigned init, unsigned end) {

    for (int i = init; i < end; i++) {
        for (int j = 0; j < w * 4; j += 4) {
            unsigned char r = image[i * w * 4 + j + 0]; // Red component
            unsigned char g = image[i * w * 4 + j + 1]; // Green component
            unsigned char b = image[i * w * 4 + j + 2]; // Blue component
            unsigned char a = image[i * w * 4 + j + 3]; // Alpha component
            int temp = j / 4;
            img[{i, temp}] = {{r, g, b, a}};
        }
    }
}


void movethread(const string_view& myfile, vector<unsigned char>& image, const unsigned & w,unsigned &h) {
    vector<unsigned char> mov;
    map<pair<int, int>, array<unsigned char, 4>> ir;
    thread t[4];
    int mini = mx, minj = mx, maxi = mn, maxj = mn;
    int c = 0;
    for (auto &u:t) {
        u = thread(mover, ref(myfile), ref(image), ref(w), h * c / 4, h * (c + 1)/4);
        c++;
    }
    for (auto &u : t) {
        u.join();
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w * 4; j += 4) {
            int temp = j / 4;
            int jmove = (int) (double(temp) * cos(ang) - double(i) * sin(ang));
            int imove = (int) (double(temp) * sin(ang) + double(i) * cos(ang));
            ir[{imove, jmove}] = img[{i, temp}];
            mini = min(imove, mini);
            maxi = max(imove, maxi);
            minj = min(jmove, minj);
            maxj = max(jmove, maxj);
        }
    }
    int rangemovej = maxj - minj + 1;
    int rangemovei = maxi - mini + 1;
    for (int i = mini; i <= maxi; i++){
        for (int j = minj; j <= maxj; j++) {
            if (ir.find({i, j}) != ir.end())
                for (const auto &s: ir[{i, j}])
                    mov.emplace_back(s);
            else
                for (const auto &s: ir[{i, j}])
                    mov.emplace_back(0);
        }
}
    encode(myfile, mov, rangemovej, rangemovei);

};









#endif //PC4_FILTER_H
