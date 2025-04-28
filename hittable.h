//
// Created by 15854 on 3/14/2024.
//



#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H


#include "aabb.h"
class material;
class hit_record{

public:
    point3 p;
    vec3 normal;
    shared_ptr<material> mat;
    double t;
    bool front_face;

    void set_normal_dir(const ray& r, const vec3& outnorm)
    {
        // we define a normal to face front if the direction of the ray is opposite the direction of the surface normal
        // if a ray comes from outside
        front_face = dot(r.direction(), outnorm) < 0;
        if(front_face)
            normal = outnorm;
        else
            normal = -outnorm;
    }
};


class hittable {
public:
    virtual ~hittable() = default;
    // const = 0, pure virtual, needs implementation
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

    virtual aabb bounding_box() const = 0;

};
#endif //RAYTRACER_HITTABLE_H
