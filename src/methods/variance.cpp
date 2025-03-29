#include "variance/variance.hpp"

double Variance::calculateError(const cv::Mat& block) const {
    cv::Scalar mean, stddev;
    cv::meanStdDev(block, mean, stddev);
    
    /* σ_𝐵𝐺𝑅^2 = (σ_𝐵^2 + σ_𝐺^2 + σ_𝑅^2) / 3 */
    return (stddev[0] * stddev[0] + stddev[1] * stddev[1] + stddev[2] * stddev[2] ) / 3.0;
}