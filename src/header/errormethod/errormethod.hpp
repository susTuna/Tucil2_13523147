/* Error Calculation Interface Header */
#ifndef ERROR_METHOD_HPP
#define ERROR_METHOD_HPP

#include "FreeImage.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class ErrorMethod{
    public:
        virtual double calculateError(FIBITMAP* image, int x, int y, int width, int height) const = 0;
        virtual ~ErrorMethod() = default;
};

#endif //ERROR_METHOD_HPP