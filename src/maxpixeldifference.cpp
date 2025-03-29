#include "maxpixeldifference.hpp"

using namespace std;

double MPD::calculateError(const cv::Mat& block) const {
    cv::Mat channels[3]; // channel BGR
    cv::split(block, channels);

    double minVal, maxVal;
    double maxDiff = 0.0;

    for (int c = 0; c < 3; ++c){
        cv::minMaxLoc(channels[c], &minVal, &maxVal);

        /* 𝐷_𝑐 = 𝑚𝑎𝑥(𝑃_𝑖,𝑐) − 𝑚𝑖𝑛(𝑃_𝑖,𝑐) */
        double diff = maxVal - minVal;
        maxDiff += diff;
    }

    /* 𝐷_𝐵𝐺𝑅 = (𝐷_𝐵 + 𝐷_𝐺 + 𝐷_𝑅) / 3 */
    return maxDiff / 3.0;
}