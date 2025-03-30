#include "imageloader/imageloader.hpp"

FIBITMAP* ImageLoader::loadImage(const string loadPath){
    FreeImage_Initialise();

    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(loadPath.c_str(), 0);
    if (fif == FIF_UNKNOWN) {
        fif = FreeImage_GetFIFFromFilename(loadPath.c_str());
    }
    
    if ((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
        FIBITMAP* image = FreeImage_Load(fif, loadPath.c_str());
        if (!image) {
            cerr << "Error: Failed to load image " << loadPath << endl;
            return nullptr;
        }

        if (FreeImage_GetBPP(image) != 24) {
            FIBITMAP* temp = FreeImage_ConvertTo24Bits(image);
            FreeImage_Unload(image);
            image = temp;
        }

        return image;
    }

    cerr << "Error: Unsupported image format " << loadPath << endl;
    return nullptr;
}