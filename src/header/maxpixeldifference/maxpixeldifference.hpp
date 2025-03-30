/* Max Pixel Difference Method Error Calculation Interface Header */
#ifndef MPD_HPP
#define MPD_HPP

#include "errormethod/errormethod.hpp"

class MPD: public ErrorMethod{
    public:
        double calculateError(FIBITMAP* image, int x, int y, int width, int height) const override;
};

#endif //MPD_HPP