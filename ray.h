//
// Created by 15854 on 3/12/2024.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include "vec3.h"

class ray {

    public:
    // constructors
        ray() {}
        ray(const point3& origin, const vec3& direction): orig(origin), dir(direction) {}

        point3 origin() const {return orig;}
        vec3 direction() const {return dir;}

        point3 at(double t) const {
            return orig + t*dir;
        }

    private:
        point3 orig;
        vec3 dir;

};

#endif //RAYTRACER_RAY_H