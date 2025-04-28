//
// Created by 15854 on 3/21/2024.
//

#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

#include <limits>
//const double infinity = std::numeric_limits<double>::infinity();
class interval  {
public:
    double min, max;

    interval() : min(infinity), max(-infinity) {}

    interval(double _min,  double _max ): min(_min), max(_max) { }

    interval(const interval& a, const interval& b) {
        // Create the interval tightly enclosing the two input intervals.
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }

    bool contains(double x) const
    {
        return min <= x && x <=  max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    double size() const {
        return max-min;
    }
    double clamp(double x) const
    {
        if(x < min)
            return min;
        if(x > max)
            return max;
        return x;
    }
    static const interval empty, universe;

};


inline const interval interval::empty(+infinity, -infinity);
inline const interval interval::universe(-infinity, +infinity);

#endif //RAYTRACER_INTERVAL_H

