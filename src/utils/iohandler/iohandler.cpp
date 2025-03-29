#include "iohandler/iohandler.hpp"
#include <limits>

string IOHandler::getImagePath(const string& prompt){
    string path;
    cout << prompt;
    getline(cin, path);
    return path;
}

int IOHandler::getMethodChoice(){
    int choice;
    cout << "\n🔥 Pilih metode perhitungan error:\n";
    cout << "1. Variance\n";
    cout << "2. Mean Absolute\n";
    cout << "3. Max Pixel Difference\n";
    cout << "4. Entropy\n";
    cout << "Pilihan (1-4): ";
    cin >> choice;
    return (choice >= 1 && choice <= 4) ? choice : 1;
}

double IOHandler::getVarianceThreshold(){
    double threshold;
    cout << "\n🎯 Masukkan nilai threshold (e.g., 500.0): ";
    cin >> threshold;
    return threshold;
}

int IOHandler::getMinBlockSize(){
    int blockSize;
    cout << "\n🟦 Masukkan ukuran blok minimum: ";
    cin >> blockSize;
    return blockSize;
}

string IOHandler::getOutputPath(){
    string path;
    cout << "\n💾 Masukkan alamat output gambar hasil: ";
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