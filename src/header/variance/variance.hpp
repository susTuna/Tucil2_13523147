/* Variance Method Error Calculation Interface Header */
#ifndef VARIANCE_HPP
#define VARIANCE_HPP

#include "errormethod.hpp"

using namespace std;

class Variance : public ErrorMethod{
    public:
        double calculateError(const cv::Mat& block) const override;
};

#endif //VARIANCE_HPP