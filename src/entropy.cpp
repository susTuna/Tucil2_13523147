#include "entropy.hpp"

double Entropy::calculateEntropy(const cv::Mat& channel) const {
    vector<int> histogram(256, 0);
    int totalPixels = channel.rows * channel.cols;

    for (int i=0; i < channel.total(); ++i){
        histogram[channel.data[i]]++;
    }

    double entropy = 0.0;

    /* 𝐻_𝑐 = −𝑁_∑_𝑖=1 𝑃_𝑐(𝑖) * 𝑙𝑜𝑔2(𝑃_𝑐(𝑖)) */
    for (int count : histogram){
        if(count > 0){
            double prob = static_cast<double>(count) / totalPixels;
            entropy -= prob * log2(prob);
        }
    }

    return entropy;
}

double Entropy::calculateError(const cv::Mat& block) const {
    vector<cv::Mat> channel;
    cv::split(block, channel);

    /* 𝐻_𝐵𝐺𝑅 = (𝐻_𝐵 + 𝐻_𝐺 + 𝐻_𝑅) / 3 */
    return (calculateEntropy(channel[0]) + calculateEntropy(channel[1]) + calculateEntropy(channel[2])) / 3.0;
}