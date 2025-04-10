#include "variance/variance.hpp"

double Variance::calculateError(FIBITMAP* image, int x, int y, int width, int height) const {
    double sumR = 0, sumG = 0, sumB = 0, sumsqR = 0, sumsqG = 0, sumsqB = 0, meanR = 0, meanG = 0, meanB = 0, varR = 0, varG = 0, varB = 0;
    int pixels = width * height;

    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width ; ++j){
            RGBQUAD color;
            if (FreeImage_GetPixelColor(image, x + j, y + i, &color)){
                sumsqR += color.rgbRed * color.rgbRed, sumsqG += color.rgbGreen * color.rgbGreen, sumsqB += color.rgbBlue * color.rgbBlue;
                sumR += color.rgbRed, sumG += color.rgbGreen, sumB += color.rgbBlue;
            }
        }
    }

    meanR = sumR / pixels, meanG = sumG / pixels, meanB = sumB / pixels;
    
    varR = sumsqR / pixels - meanR * meanR;
    varG = sumsqG / pixels - meanG * meanG;
    varB = sumsqB / pixels - meanB * meanB;
    
    /* σ_𝑅𝐺𝐵^2 = (σ_𝑅^2 + σ_𝐺^2 + σ_𝐵^2) / 3 */
    return (varR + varG + varB) / 3.0;
}