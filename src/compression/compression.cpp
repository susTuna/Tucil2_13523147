#include "compression/compression.hpp"

using namespace std::chrono;

Compression::Compression(FIBITMAP* image, ErrorMethod* method, FREE_IMAGE_FORMAT ext, const string &inpath, const string &outpath, double errThreshold, int minBlockSize, float targetRatio) : image(image), method(method), ext(ext), imagePath(inpath), outputPath(outpath), errThreshold(errThreshold), minBlockSize(minBlockSize), compressionRatio(0.0f), targetRatio(targetRatio){}

Compression::~Compression(){}

FIBITMAP* Compression::buildAndReconstruct(){
    FIBITMAP* outputImg = nullptr;
    QuadTree qTree;

    qTree.buildTree(image, method, errThreshold, minBlockSize);
    qTree.reconstructImg(outputImg);

    depth = qTree.getDepth();
    nodes = qTree.getNodesCount();

    return outputImg;
}

double Compression::adjustThreshold(double low, double high, double tolerance){
    const int maxLoop = 20;
    double bestThreshold = errThreshold;

    DWORD oSize = FreeImage_GetDIBSize(image);

    for (int i = 0; i < maxLoop; ++i){
        double mid = (low + high) / 2.0;
        errThreshold = mid;

        FIBITMAP* tempOutput = buildAndReconstruct();
        DWORD cSize = FreeImage_GetDIBSize(tempOutput);
        double currentCompression = (1.0 - static_cast<double>(cSize) / static_cast<double>(oSize)) * 100.0;
        FreeImage_Unload(tempOutput);

        if (fabs(currentCompression - targetRatio) < tolerance){
            bestThreshold = mid;
            break;
        } else if (currentCompression < targetRatio){
            low = mid;
        } else {
            high = mid;
        }
        bestThreshold = mid;
    }
    return bestThreshold;
}

void Compression::adjustParam(){
    if (targetRatio == 0.0f){
        return;
    }

    double bestThreshold = errThreshold;
    double bestBlockSize = minBlockSize;
    double bestDiff = numeric_limits<double>::max();
    double tolerance = 0.1;

    int candidateBlockSize[] = {1, 4, 8, 16, 32, 64, 128, 256};
    int numCanditates = sizeof(candidateBlockSize) / sizeof(int);

    DWORD oSize = FreeImage_GetDIBSize(image);

    for (int i = 0; i < numCanditates; ++i){
        int candidate = candidateBlockSize[i];
        minBlockSize = candidate;

        double low = 0;
        double high = 255;
        double candidateThreshold = adjustThreshold(low, high, tolerance);
        errThreshold = candidateThreshold;

        FIBITMAP* tempOutput = buildAndReconstruct();
        DWORD cSize = FreeImage_GetDIBSize(tempOutput);
        double currentCompression = (1.0 - static_cast<double>(cSize) / static_cast<double>(oSize)) * 100.0;
        FreeImage_Unload(tempOutput);

        double diff = fabs(currentCompression - targetRatio);
        if (diff < bestDiff){
            bestDiff = diff;
            bestThreshold = candidateThreshold;
            bestBlockSize = candidate;
        }
    }

    errThreshold = bestThreshold;
    minBlockSize = bestBlockSize;
}

void Compression::compress(){
    auto start = high_resolution_clock::now();

    if (targetRatio > 0.0f){
        adjustParam();
    }

    FIBITMAP* outputImg = buildAndReconstruct();
    auto end = high_resolution_clock::now();
    duration<double> execTime = end - start;
    durations = execTime.count();

    if (FreeImage_Save(ext, outputImg, outputPath.c_str(), (ext == FIF_JPEG) ? 100 : 0)) {
        cout << "\nImage saved successfully at " << outputPath << "\n";
    } else {
        throw runtime_error("Error: Failed to save the image!");
    }

    auto originalSize = filesystem::file_size(imagePath);
    auto compressedSize = filesystem::file_size(outputPath);
    origSize = originalSize;
    compSize = compressedSize;
    compressionRatio = (1.0 - (float)compressedSize / originalSize) * 100;

    FreeImage_Unload(outputImg);
    outputImg = nullptr;
}

float Compression::getCompressionRatio() const{
    return compressionRatio;
}

int Compression::getDepth() const{
    return depth;
}

int Compression::getNodesCount() const{
    return nodes;
}

double Compression::getDuration() const{
    return durations;
}

double Compression::getOrigSize() const{
    return origSize;
}

double Compression::getCompSize() const{
    return compSize;
}