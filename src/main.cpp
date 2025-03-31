#include <chrono>
#include "quadtree/quadtree.hpp"
#include "iohandler/iohandler.hpp"
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
        string outputPath = IOHandler::getOutputPath();
        ErrorMethod* method = IOHandler::chooseErrorMethod(methodChoice);
        FREE_IMAGE_FORMAT ext = IOHandler::getImageFormat(outputPath);

        FIBITMAP* image = ImageLoader::loadImage(imagePath);

        QuadTree qTree;
        
        auto start = chrono::high_resolution_clock::now();
        qTree.buildTree(image, method, varianceThreshold, minBlockSize);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> execTime = end - start;

        FIBITMAP* outputImg = nullptr;
        qTree.reconstructImg(outputImg);
        
        if (FreeImage_Save(ext, outputImg, outputPath.c_str(), (ext == FIF_JPEG) ? 100 : 0)) {
            cout << "\n✅ Image saved successfully at " << outputPath << "\n";
        } else {
            throw runtime_error("Error: Failed to save the image!");
        }

        auto originalSize = filesystem::file_size(imagePath);
        auto compressedSize = filesystem::file_size(outputPath);
        double compressionRatio = (1.0 - (double)compressedSize / originalSize) * 100;

        int depth = qTree.getDepth();
        int nodeCount = qTree.getNodesCount();

        cout << "\n================================================================\n";
        cout << "✅ Compression Complete!\n";
        cout << "================================================================\n";
        cout << "⏳ Processing Time     : " << execTime.count() << " seconds\n";
        cout << "Original Size         : " << originalSize / 1024 << " KB\n";
        cout << "Compressed Size       : " << compressedSize / 1024 << " KB\n";
        cout << "Compression Percentage: " << compressionRatio << "%\n";
        cout << "Quadtree Depth        : " << depth << "\n";
        cout << "Total Nodes           : " << nodeCount << "\n";
        cout << "================================================================\n";

        delete method;
        FreeImage_Unload(image);
        FreeImage_Unload(outputImg);
        image = nullptr;
        outputImg = nullptr;
        FreeImage_DeInitialise();

    } catch (const exception& e){
        cerr << "\n❌ Exception: " << e.what() << "\n";
        return 1;
    } catch (...){
        cerr << "\n❌ Unknown error occurred!\n";
        return 1;
    }
    
    return 0;
}