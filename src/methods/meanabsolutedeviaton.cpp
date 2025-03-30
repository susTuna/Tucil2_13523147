#include "meanabsolutedeviation/meanabsolutedeviation.hpp"

double MAD::calculateError(FIBITMAP* image, int x, int y, int width, int height) const {
    double sumR = 0, sumG = 0, sumB = 0, meanR = 0, meanG = 0, meanB = 0, madR = 0, madG = 0, madB = 0;
    int pixels = width * height;
    RGBQUAD color;

    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width ; ++j){
            if (FreeImage_GetPixelColor(image, x + j, y + i, &color)){
                sumR += color.rgbRed, sumG += color.rgbGreen, sumB += color.rgbBlue;
            }
        }
    }

    meanR = sumR / pixels, meanG = sumG / pixels, meanB = sumB / pixels;

    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width ; ++j){
            if (FreeImage_GetPixelColor(image, x + j, y + i, &color)){
                madR += fabs(color.rgbRed - meanR), madG += fabs(color.rgbGreen - meanG), madB += fabs(color.rgbBlue - meanB);
            }
        }
    }

    madR /= pixels, madG /= pixels, madB /= pixels;

    /* 𝑀𝐴𝐷_𝑅𝐺𝐵 = (𝑀𝐴𝐷_𝑅 + 𝑀𝐴𝐷_𝐺 + 𝑀𝐴𝐷_𝐵) / 3 */
    return (madR + madG + madB) / 3.0;
}