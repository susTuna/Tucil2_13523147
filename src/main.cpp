#include "compression/compression.hpp"
#include "imageloader/imageloader.hpp"
#include "ascii/ascii.hpp"

int main(){
    try{
        Ascii yuuka;
        yuuka.displayAscii();

        string imagePath = IOHandler::getImagePath("\nEnter the image file path: ");
        int methodChoice = IOHandler::getMethodChoice();
        double varianceThreshold = IOHandler::getVarianceThreshold();
        int minBlockSize = IOHandler::getMinBlockSize();
        float targetRatio = IOHandler::getTargetRatio();
        string outputPath = IOHandler::getOutputPath();
        ErrorMethod* method = IOHandler::chooseErrorMethod(methodChoice);
        FREE_IMAGE_FORMAT ext = IOHandler::getImageFormat(outputPath);

        FIBITMAP* image = ImageLoader::loadImage(imagePath);

        Compression compressor(image, method, ext, imagePath, outputPath, varianceThreshold, minBlockSize, targetRatio);
        compressor.compress();

        double originalSize = compressor.getOrigSize();
        double compressedSize = compressor.getCompSize();
        float compressionRatio = compressor.getCompressionRatio();
        double execTime = compressor.getDuration();
        int depth = compressor.getDepth();
        int nodeCount = compressor.getNodesCount();

        cout << "\n================================================================\n";
        cout << "Compression Complete!\n";
        cout << "================================================================\n";
        cout << "Processing Time     : " << execTime << " seconds\n";
        cout << "Original Size         : " << originalSize / 1024 << " KB\n";
        cout << "Compressed Size       : " << compressedSize / 1024 << " KB\n";
        cout << "Compression Percentage: " << compressionRatio << "%\n";
        cout << "Quadtree Depth        : " << depth << "\n";
        cout << "Total Nodes           : " << nodeCount << "\n";
        cout << "================================================================\n";

        delete method;
        FreeImage_Unload(image);
        image = nullptr;
        FreeImage_DeInitialise();

    } catch (const exception& e){
        cerr << "\nException: " << e.what() << "\n";
        return 1;
    } catch (...){
        cerr << "\nUnknown error occurred!\n";
        return 1;
    }
    
    return 0;
}