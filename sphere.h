//
// Created by 15854 on 3/14/2024.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include "interval.h"
// inherits from hittable
class sphere : public hittable {
    public:
    sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 ac = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(r.direction(), ac);
        auto c = dot(ac, ac) - radius * radius;
        auto discriminant = b * b - 4 * a * c;

        // to get the normal we return the solution for t
        if (discriminant < 0)
            return false;

        // find nearest root to tmax and tmin
        auto root = (-b - sqrt(discriminant)) / (2 * a);
        if(!ray_t.contains(root))
        {
            root = (-b + sqrt(discriminant)) / (2 * a);
            if(!ray_t.surrounds(root))
            {
                return false;
            }
        }


        rec.t = root;
        rec.p = r.at(root);
        rec.normal = (rec.p - center) / radius;
        // for a sphere we can obtain a normal by getting the hitpoint - the center, we can normalize by dividing by r
        vec3 outnorm = (rec.p - center) / radius;
        rec.set_normal_dir(r,outnorm);
        return true;

    }

private:
    point3 center;
    double radius;
};

#endif //RAYTRACER_SPHERE_H
