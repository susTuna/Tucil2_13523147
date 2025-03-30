/* Entropy Method Error Calculation Interface Header */
#ifndef ENTROPY_HPP
#define ENTROPY_HPP

#include "errormethod/errormethod.hpp"

class Entropy: public ErrorMethod{
    public:
        double calculateError(FIBITMAP* image, int x, int y, int width, int height) const override;
};

#endif //ENTROPY_HPP