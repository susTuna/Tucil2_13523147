#include "variance/variance.hpp"

double Variance::calculateError(FIBITMAP* image, int x, int y, int width, int height) const {
    double sumR, sumG, sumB, meanR, meanG, meanB, varR, varG, varB = 0;
    int pixels = width * height;

    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width ; ++j){
            RGBQUAD color;
            if (FreeImage_GetPixelColor(image, x + j, y + i, &color)){
                sumR += color.rgbRed, sumG += color.rgbGreen, sumB += color.rgbBlue;
            }
        }
    }

    meanR = sumR / pixels, meanG = sumG / pixels, meanB = sumB / pixels;
    
    varR = (sumR * sumR) / pixels - meanR * meanR;
    varG = (sumG * sumG) / pixels - meanG * meanG;
    varB = (sumB * sumB) / pixels - meanB * meanB;
    
    /* σ_𝑅𝐺𝐵^2 = (σ_𝑅^2 + σ_𝐺^2 + σ_𝐵^2) / 3 */
    return (varR + varG + varB) / 3.0;
}