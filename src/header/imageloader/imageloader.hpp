/* ImageLoader Header File */
#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <iostream>
#include <FreeImage.h>

using namespace std;

class ImageLoader{
    public:
        static FIBITMAP* loadImage(const string loadPath);
};

#endif //IMAGELOADER_HPP