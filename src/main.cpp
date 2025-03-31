#include <chrono>
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
        cout << "\n✅ Gambar berhasil disimpan di " << outputPath << "\n";
    } else {
        cerr << "\n❌ Gagal menyimpan gambar!\n";
    }

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

    delete method;
    FreeImage_Unload(image);
    FreeImage_Unload(outputImg);
    FreeImage_DeInitialise();

    return 0;
}