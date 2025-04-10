#include "maxpixeldifference/maxpixeldifference.hpp"

double MPD::calculateError(FIBITMAP* image, int x, int y, int width, int height) const{
    double maxR = 0, maxG = 0, maxB = 0, minR = 255, minG = 255, minB = 255;
    RGBQUAD color;

    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width ; ++j){
            if (FreeImage_GetPixelColor(image, x + j, y + i, &color)){
                maxR = max(maxR, (double)color.rgbRed), maxG = max(maxG, (double)color.rgbGreen), maxB = max(maxB, (double)color.rgbBlue);
                minR = min(minR, (double)color.rgbRed), minG = min(minG, (double)color.rgbGreen), minB = min(minB, (double)color.rgbBlue);
            }
        }
    }

    /* 𝐷_𝑅𝐺𝐵 = (𝐷_𝑅 + 𝐷_𝐺 + 𝐷_𝐵) / 3 */
    return (maxR - minR + maxG - minG + maxB - minB) / 3.0;
}