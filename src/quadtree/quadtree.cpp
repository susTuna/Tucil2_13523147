#include "quadtree/quadtree.hpp"

int QuadTree::Node::nodeCount = 0;

QuadTree::Node::Node(cv::Rect region, int depth = 0) : region(region), avgColor(0, 0, 0, 0), depth(depth){
    for (int i = 0; i < 4 ; ++i) children[i] = nullptr;
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

void QuadTree::subdivide(Node* node, const cv::Mat& image){
    /* Check whether pixel size has reached the minimum size */
    if(node->region.width <= minBlockSize || node->region.height <= minBlockSize){
        cv::Scalar avgColor = cv::mean(image(node->region));
        node->avgColor = avgColor;
        return;
    }

    cv::Mat block = image(node->region);
    double error = errorMethod->calculateError(block);

    /* Check whether the error has reached the threshold */
    if (error > varThreshold){
        int halfWidth = node->region.width / 2;
        int halfHeight = node->region.height / 2;

        /* Divide */
        node->children[0] = new Node(cv::Rect(node->region.x, node->region.y, halfWidth, halfHeight), node->depth + 1);
        node->children[1] = new Node(cv::Rect(node->region.x + halfWidth, node->region.y, halfWidth, halfHeight), node->depth + 1);
        node->children[2] = new Node(cv::Rect(node->region.x, node->region.y + halfHeight, halfWidth, halfHeight), node->depth + 1);
        node->children[3] = new Node(cv::Rect(node->region.x + halfWidth, node->region.y + halfHeight, halfWidth, halfHeight), node->depth + 1);
        
        /* Recursion */
        for (int i = 0; i < 4; ++i){
            subdivide(node->children[i], image);
        }
    } else{
        node->avgColor = cv::mean(block);
    }
}

void QuadTree::normalizeColor(Node* node, cv::Mat& image){
    if (!node || !node->children[0]) return;

    cv::Scalar avgColor(0, 0, 0);
    int count = 0;
    
    for (int i = 0; i < 4; i++){
        if (node->children[i]){
            normalizeColor(node->children[i], image);
            avgColor += node->children[i]->avgColor;
            count++;
        }
    }

    if (count > 0){
        node->avgColor = avgColor / count;
    }
}

void QuadTree::buildTree(const cv::Mat& image, const ErrorMethod* method, double threshold, int minSize){
    errorMethod = method;
    varThreshold = threshold;
    minBlockSize = minSize;
    root = new Node(cv::Rect(0,0,image.cols,image.rows));
    subdivide(root, image);
}

void QuadTree::reconstructNode(Node* node, cv::Mat& image){
    if (!node) return;

    if (!node->children[0]){
        cv::rectangle(image, node->region, node->avgColor, cv::FILLED);
    } else{
        for (int i = 0; i < 4; ++i){
            reconstructNode(node->children[i], image);
        }
    }
}

void QuadTree::reconstructImg(cv::Mat& output){
    if (!root) return;
    output = cv::Mat::zeros(root->region.height, root->region.width, CV_8UC3);
    reconstructNode(root, output);
}

int QuadTree::getDepth(){
    if (!root) return 0;
    return root->depth;
}

int QuadTree::getNodesCount(){
    return Node::nodeCount;
}