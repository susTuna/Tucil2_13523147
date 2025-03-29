/* Input/Output Handler Header File */
#ifndef IOHANDLER_HPP
#define IOHANDLER_HPP

#include "variance/variance.hpp"
#include "meanabsolutedeviation/meanabsolutedeviation.hpp"
#include "maxpixeldifference/maxpixeldifference.hpp"
#include "entropy/entropy.hpp"

class IOHandler{
    public:
        static string getImagePath(const string& prompt);
        static int getMethodChoice();
        static double getVarianceThreshold();
        static int getMinBlockSize();
        static string getOutputPath();
        static ErrorMethod* chooseErrorMethod(int choice);
};

#endif //IOHANDLER_HPP