/* Mean Absolute Deviation Method Error Calculation Interface Header */
#ifndef MAD_HPP
#define MAD_HPP

#include "errormethod/errormethod.hpp"

class MAD: public ErrorMethod{
    public:
        double calculateError(const cv::Mat& block) const override;
};

#endif //MAD_HPP