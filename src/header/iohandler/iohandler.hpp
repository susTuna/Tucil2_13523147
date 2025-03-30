/* Input/Output Handler Header File */
#ifndef IOHANDLER_HPP
#define IOHANDLER_HPP

#include "variance/variance.hpp"
#include "meanabsolutedeviation/meanabsolutedeviation.hpp"
#include "maxpixeldifference/maxpixeldifference.hpp"
#include "entropy/entropy.hpp"
#include <limits>
#include <filesystem>
#include <algorithm>

class IOHandler{
    public:
        static string getImagePath(const string& prompt);
        static int getMethodChoice();
        static double getVarianceThreshold();
        static int getMinBlockSize();
        static string getOutputPath();
        static ErrorMethod* chooseErrorMethod(int choice);
        static FREE_IMAGE_FORMAT getImageFormat(const string& filename);
};

#endif //IOHANDLER_HPP