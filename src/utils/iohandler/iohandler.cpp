#include "iohandler/iohandler.hpp"

string IOHandler::getImagePath(const string& prompt){
    string path;
    cout << prompt;
    getline(cin, path);
    return path;
}

int IOHandler::getMethodChoice(){
    int choice;
    cout << "\nSelect an error calculation method:\n";
    cout << "1. Variance\n";
    cout << "2. Mean Absolute\n";
    cout << "3. Max Pixel Difference\n";
    cout << "4. Entropy\n";
    cout << "Choice (1-4): ";
    cin >> choice;
    return (choice >= 1 && choice <= 4) ? choice : 1;
}

double IOHandler::getVarianceThreshold(){
    double threshold;
    cout << "\nEnter threshold value: ";
    cin >> threshold;
    return threshold;
}

int IOHandler::getMinBlockSize(){
    int blockSize;
    cout << "\nEnter minimum block size: ";
    cin >> blockSize;
    return blockSize;
}

float IOHandler::getTargetRatio(){
    float ratio;
    cout << "\nEnter target compression ratio (0.0 - 100.0): ";
    cin >> ratio;
    return (ratio >= 0.0f && ratio <= 100.0f) ? ratio : 0.0f;
}

string IOHandler::getOutputPath(){
    string path;
    cout << "\nEnter the output image path: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, path);
    return path;
}

ErrorMethod* IOHandler::chooseErrorMethod(int choice){
    switch (choice){
    case 1: return new Variance();
    case 2: return new MAD();
    case 3: return new MPD();
    case 4: return new Entropy();
    default: return nullptr;
    }
}

FREE_IMAGE_FORMAT IOHandler::getImageFormat(const string& filename){
    string ext = filesystem::path(filename).extension().string();

    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == ".png") return FIF_PNG;
    if (ext == ".jpg" || ext == ".jpeg") return FIF_JPEG;
    if (ext == ".bmp") return FIF_BMP;
    if (ext == ".tiff") return FIF_TIFF;
    if (ext == ".gif") return FIF_GIF;
    if (ext == ".tga") return FIF_TARGA;

    return FIF_UNKNOWN;
}