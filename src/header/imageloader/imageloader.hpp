/* ImageLoader Header File */
#ifndef IMAGELOADER_HPP
#define IMAGELOADER_HPP

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class ImageLoader{
    public:
        static cv::Mat loadImage(const string& loadPath);
};

#endif //IMAGELOADER_HPP