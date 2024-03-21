//
// Created by 15854 on 3/21/2024.
//

#ifndef RAYTRACER_INTERVAL_H
#define RAYTRACER_INTERVAL_H

#include <limits>
const double infinity = std::numeric_limits<double>::infinity();
class interval  {
public:
    double min, max;

    interval() : min(infinity), max(-infinity) {}

    interval(double _min,  double _max ): min(_min), max(_max)
    {

    }

    bool contains(double x) const
    {
        return min <= x && x <=  max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    static const interval empty, universe;

};

const static interval empty   (+infinity, -infinity);
const static interval universe(-infinity, +infinity);


#endif //RAYTRACER_INTERVAL_H
