/* Entropy Method Error Calculation Interface Header */
#ifndef ENTROPY_HPP
#define ENTROPY_HPP

#include "errormethod.hpp"

using namespace std;

class Entropy: public ErrorMethod{
    public:
        double calculateError(const cv::Mat& block) const override;
};

#endif //ENTROPY_HPP