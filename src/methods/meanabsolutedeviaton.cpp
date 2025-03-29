#include "meanabsolutedeviation/meanabsolutedeviation.hpp"

double MAD::calculateError(const cv::Mat& block) const{
    cv::Scalar mean = cv::mean(block);
    cv::Mat absDiff;
    cv::absdiff(block, mean, absDiff);
    cv::Scalar mad = cv::mean(absDiff);

    /* 𝑀𝐴𝐷_𝐵𝐺𝑅 = (𝑀𝐴𝐷_𝐵 + 𝑀𝐴𝐷_𝐺 + 𝑀𝐴𝐷_𝑅) / 3 */
    return (mad[0] + mad[1] + mad[2]) / 3.0;
}