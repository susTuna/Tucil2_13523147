/* Entropy Method Error Calculation Interface Header */
#ifndef ENTROPY_HPP
#define ENTROPY_HPP

#include "errormethod.hpp"

class Entropy: public ErrorMethod{
    public:
        double calculateEntropy(const cv::Mat& channel) const;
        double calculateError(const cv::Mat& block) const override;
};

#endif //ENTROPY_HPP