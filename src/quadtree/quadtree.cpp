#include "quadtree/quadtree.hpp"

int QuadTree::Node::nodeCount = 0;

QuadTree::Node::Node(int x, int y, int width, int height, int depth) : x(x), y(y), width(width), height(height), depth(depth){
    for (int i = 0; i < 4 ; ++i) children[i] = nullptr;
    if (depth > maxDepth) maxDepth = depth;
    ++nodeCount;
}

QuadTree::Node::~Node(){
    for (int i = 0; i < 4 ; ++i) delete children[i];
    --nodeCount;
}

QuadTree::QuadTree() : root(nullptr), minBlockSize(0), varThreshold(0.0), errorMethod(nullptr){}

QuadTree::~QuadTree(){
    delete root;
}

void QuadTree::subdivide(Node* node, FIBITMAP* image){
    /* Calculate average color for this block */
    node->avgColor = calculateAverageColor(image, node->x, node->y, node->width, node->height);

    /* Calculate error for this block */
    double error = errorMethod->calculateError(image, node->x, node->y, node->width, node->height);

    /* Check whether pixel size has reached the minimum size or error is less than threshold */
    if(node->width <= minBlockSize || node->height <= minBlockSize || error <= varThreshold) {
        node->leaf = true;
        return;
    }

    int halfWidth = node->width / 2;
    int halfHeight = node->height / 2;

    /* Divide */
    node->children[0] = new Node(node->x, node->y, halfWidth, halfHeight, node->depth + 1);
    node->children[1] = new Node(node->x + halfWidth, node->y, halfWidth, halfHeight, node->depth + 1);
    node->children[2] = new Node(node->x, node->y + halfHeight, halfWidth, halfHeight, node->depth + 1);
    node->children[3] = new Node(node->x + halfWidth, node->y + halfHeight, halfWidth, halfHeight, node->depth + 1);
    
    /* Recursion */
    for (int i = 0; i < 4; ++i){
        subdivide(node->children[i], image);
    }
}

RGBQUAD QuadTree::calculateAverageColor(FIBITMAP* image, int x, int y, int width, int height) const{
    double sumR = 0, sumG = 0, sumB = 0;
    int pixelCount = width * height;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            RGBQUAD color;
            if (FreeImage_GetPixelColor(image, x + j, y + i, &color)) {
                sumR += color.rgbRed;
                sumG += color.rgbGreen;
                sumB += color.rgbBlue;
            }
        }
    }

    RGBQUAD avgColor;
    avgColor.rgbRed = static_cast<BYTE>(sumR / pixelCount);
    avgColor.rgbGreen = static_cast<BYTE>(sumG / pixelCount);
    avgColor.rgbBlue = static_cast<BYTE>(sumB / pixelCount);
    
    return avgColor;
}

void QuadTree::buildTree(FIBITMAP* image, const ErrorMethod* method, double threshold, int minSize){
    errorMethod = method;
    varThreshold = threshold;
    minBlockSize = minSize;
    
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    root = new Node(0, 0, width, height, 0);
    subdivide(root, image);
}

void QuadTree::reconstructNode(Node* node, FIBITMAP* image){
    if (!node) return;

    if (node->leaf){
        for(int i = 0; i < node->height; ++i){
            for(int j = 0; j < node->width; ++j){
                FreeImage_SetPixelColor(image, node->x + j, node->y + i, &node->avgColor);
            }
        }
    } else{
        for (int i = 0; i < 4; ++i){
            reconstructNode(node->children[i], image);
        }
    }
}

void QuadTree::reconstructImg(FIBITMAP* output){
    if (!root) return;
    output = FreeImage_Allocate(root->width, root->height, 24);
    reconstructNode(root, output);
}

int QuadTree::getDepth() const{
    return Node::maxDepth;
}

int QuadTree::getNodesCount() const{
    return Node::nodeCount;
}