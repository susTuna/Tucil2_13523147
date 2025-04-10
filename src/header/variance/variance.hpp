/* Variance Method Error Calculation Interface Header */
#ifndef VARIANCE_HPP
#define VARIANCE_HPP

#include "errormethod/errormethod.hpp"

class Variance : public ErrorMethod{
    public:
        double calculateError(FIBITMAP* image, int x, int y, int width, int height) const override;
};

#endif //VARIANCE_HPP