/* Compression % (BONUS) Header File */
#ifndef COMPRESSION_HPP
#define COMPRESSION_HPP

#include "quadtree/quadtree.hpp"
#include "iohandler/iohandler.hpp"
#include <chrono>

class Compression{
    private:
        FIBITMAP* image;
        string imagePath;
        string outputPath;
        double errThreshold;
        int minBlockSize;
        float compressionRatio;
        float targetRatio;
        ErrorMethod* method;
        int depth;
        int nodes;
        double durations;
        double origSize;
        double compSize;
        FREE_IMAGE_FORMAT ext;

        double adjustThreshold(double low, double high, double tolerance);
        void adjustParam();
        FIBITMAP* buildAndReconstruct();
    public:
        Compression(FIBITMAP* image, ErrorMethod* method, FREE_IMAGE_FORMAT ext, const string& imagePath, const string& outputPath, double errThreshold, int minBlockSize, float targetRatio = 0.0f);
        ~Compression();
        void compress();
        float getCompressionRatio() const;
        int getDepth() const;
        int getNodesCount() const;
        double getDuration() const;
        double getOrigSize() const;
        double getCompSize() const;

};

#endif //COMPRESSION_HPP