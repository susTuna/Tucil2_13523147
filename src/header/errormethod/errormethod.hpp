/* Error Calculation Interface Header */
#ifndef ERROR_METHOD_HPP
#define ERROR_METHOD_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

class ErrorMethod{
    public:
        virtual double calculateError(const cv::Mat& block) const = 0;
        virtual ~ErrorMethod() = default;
};

#endif //ERROR_METHOD_HPP