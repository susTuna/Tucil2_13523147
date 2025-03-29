#include <chrono>
#include <filesystem>
#include "quadtree/quadtree.hpp"
#include "iohandler/iohandler.hpp"
#include "imageloader/imageloader.hpp"

int main(){
    cout << "============================================\n";
    cout << "🔥 QUADTREE IMAGE COMPRESSION TOOL 🔥\n";
    cout << "============================================\n\n";

    string imagePath = IOHandler::getImagePath("📂 Masukkan alamat gambar: ");
    int methodChoice = IOHandler::getMethodChoice();
    double varianceThreshold = IOHandler::getVarianceThreshold();
    int minBlockSize = IOHandler::getMinBlockSize();
    string outputPath = IOHandler::getOutputPath();
    ErrorMethod* method = IOHandler::chooseErrorMethod(methodChoice);

    cv::Mat image = ImageLoader::loadImage(imagePath);

    QuadTree qTree;
    
    auto start = chrono::high_resolution_clock::now();
    qTree.buildTree(image, method, varianceThreshold, minBlockSize);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> execTime = end - start;

    cv::Mat outputImg;
    qTree.reconstructImg(outputImg);
    cv::imwrite(outputPath, outputImg);

    auto originalSize = filesystem::file_size(imagePath);
    auto compressedSize = filesystem::file_size(outputPath);
    double compressionRatio = (1.0 - (double)compressedSize / originalSize) * 100;

    int depth = qTree.getDepth();
    int nodeCount = qTree.getNodesCount();

    cout << "\n============================================\n";
    cout << "✅ Kompresi Selesai!\n";
    cout << "============================================\n";
    cout << "⏳ Waktu Eksekusi     : " << execTime.count() << " detik\n";
    cout << "📏 Ukuran Sebelum     : " << originalSize / 1024 << " KB\n";
    cout << "📏 Ukuran Setelah     : " << compressedSize / 1024 << " KB\n";
    cout << "📉 Persentase Kompresi: " << compressionRatio << "%\n";
    cout << "🌳 Kedalaman Pohon    : " << depth << "\n";
    cout << "🔢 Jumlah Simpul      : " << nodeCount << "\n";
    cout << "============================================\n";

    cv::imshow("Original Image", image);
    cv::imshow("Compressed Image", outputImg);
    cv::waitKey(0);

    delete method;

    return 0;
}
