#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <cstdlib>
// #include <random>

#include "constants.h"

// Utility functions
inline double degrees_to_radius(double degrees) { return degrees * pi / 180; }

// inline double random_double() {
//     static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//     static std::mt19937 generator;
//     return distribution(generator);
// }

inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(int min, int max) { return min + (max - min) * random_double(); }

#endif
