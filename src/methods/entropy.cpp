#include "entropy/entropy.hpp"

double Entropy::calculateError(FIBITMAP* image, int x, int y, int width, int height) const{
    vector<int> histR(256,0), histG(256,0), histB(256,0);
    double entropyR = 0, entropyG = 0, entropyB = 0, probR = 0, probG = 0, probB = 0;
    int pixels = width * height;
    RGBQUAD color;

    for (int i = 0; i < height; ++i){
        for(int j = 0; j < width ; ++j){
            if (FreeImage_GetPixelColor(image, x + j, y + i, &color)){
                ++histR[color.rgbRed], ++histG[color.rgbGreen], ++histB[color.rgbBlue];
            }
        }
    }

    for (int i = 0; i < 256; ++i){
        probR = (double)histR[i] / pixels;
        probG = (double)histG[i] / pixels;
        probB = (double)histB[i] / pixels;

        if (probR > 0) entropyR -= probR * log2(probR);
        if (probG > 0) entropyG -= probG * log2(probG);
        if (probB > 0) entropyB -= probB * log2(probB);
    }
    
    /* 𝐻_𝑅𝐺𝐵 = (𝐻_𝑅 + 𝐻_𝐺 + 𝐻_𝐵) / 3 */
    return (entropyR + entropyG + entropyB) / 3.0;
}