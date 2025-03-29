/* Input/Output Handler Header File */
#ifndef IOHANDLER_HPP
#define IOHANDLER_HPP

#include "variance.hpp"
#include "meanabsolutedeviation.hpp"
#include "maxpixeldifference.hpp"
#include "entropy.hpp"

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