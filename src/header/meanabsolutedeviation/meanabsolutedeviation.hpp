/* Mean Absolute Deviation Method Error Calculation Interface Header */
#ifndef MAD_HPP
#define MAD_HPP

#include "errormethod.hpp"

using namespace std;

class MAD: public ErrorMethod{
    public:
        double calculateError(const cv::Mat& block) const override;
};

#endif //MAD_HPP