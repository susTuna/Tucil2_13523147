/* Max Pixel Difference Method Error Calculation Interface Header */
#ifndef MPD_HPP
#define MPD_HPP

#include "errormethod/errormethod.hpp"

class MPD: public ErrorMethod{
    public:
        double calculateError(const cv::Mat& block) const override;
};

#endif //MPD_HPP