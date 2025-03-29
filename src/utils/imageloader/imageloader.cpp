#include "imageloader.hpp"

cv::Mat ImageLoader::loadImage(const string& loadPath){
    cv::Mat image = cv::imread(loadPath);
    if (image.empty()){
        cerr << "Error: Failed to load image!" << endl;
        exit(-1);
    }
    return image;
}