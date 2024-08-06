#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdlib>

#include "constants.h"

// Utility functions
inline double degrees_to_radius(double degrees) { return degrees * pi / 180; }

inline double random_double() { return std::rand() / (RAND_MAX + 1.0); }

inline double random_double(int min, int max) { return min + (max - min) * random_double(); }

#endif
