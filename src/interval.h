#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.h"

class interval {
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}

    interval(double min, double max) : min(min), max(max) {}

    double size() const { return max - min; }

    bool contains(double x) const { return this->min <= x && x <= this->max; }

    bool surrounds(double x) const { return this->min < x && x < this->max; }

    double clamp(double x) const {
        if (x < this->min) {
            return this->min;
        } else if (x > this->max) {
            return this->max;
        }
        return x;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif
