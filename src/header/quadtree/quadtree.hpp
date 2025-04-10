/* QuadTree Header File */
#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "errormethod/errormethod.hpp"

class QuadTree{
    private:
        struct Node{
            int x, y, width, height, depth;
            RGBQUAD avgColor;
            Node* children[4];
            static int nodeCount;
            static int maxDepth;

            Node(int x, int y, int width, int height, int depth);
            ~Node();
            bool leaf = false;
        };

        Node* root;
        int minBlockSize;
        double varThreshold;
        const ErrorMethod* errorMethod;

        void subdivide(Node* node, FIBITMAP* image);
        RGBQUAD calculateAverageColor(FIBITMAP* image, int x, int y, int width, int height) const;
        void reconstructNode(Node* node, FIBITMAP* image);

    public:
        QuadTree();
        ~QuadTree();

        void buildTree(FIBITMAP* image, const ErrorMethod* method, double threshold, int minSize);
        void reconstructImg(FIBITMAP*& output);
        int getDepth() const;
        int getNodesCount() const;
};

#endif // QUADTREE_HPP