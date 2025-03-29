/* QuadTree Header File */
#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "errormethod.hpp"

class QuadTree{
    private:
        struct Node{
            cv::Rect region;
            cv::Scalar avgColor;
            Node* children[4];
            int depth;
            static int nodeCount;

            Node(cv::Rect region, int depth);
            ~Node();
        };

        Node* root;
        int minBlockSize;
        double varThreshold;
        const ErrorMethod* errorMethod;

        void subdivide(Node* node, const cv::Mat& image);
        void normalizeColor(Node* node, cv::Mat& image);
    public:
        QuadTree();
        ~QuadTree();
        void buildTree(const cv::Mat& image, const ErrorMethod* method, double threshold, int minSize);
        void reconstructNode(Node* node, cv::Mat& image);
        void reconstructImg(cv::Mat& output);
        int getDepth();
        int getNodesCount();
};

#endif //QUADTREE_HPP