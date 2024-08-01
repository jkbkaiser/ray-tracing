#ifndef RAY_TRACING
#define RAY_TRACING

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// Common headers
#include "color.h"
#include "constants.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Utility functions
inline double degrees_to_radius(double degrees) { return degrees * pi / 180; }

#endif
