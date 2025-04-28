//
// Created by 15854 on 3/14/2024.
//

#ifndef RAYTRACER_HITTABLE_LIST_H
#define RAYTRACER_HITTABLE_LIST_H
#include "hittable.h"
#include "interval.h"
#include "aabb.h"
#include <memory>
#include <vector>


using namespace std;

class hittable_list : public hittable {
public:
    vector<shared_ptr<hittable>> objects;

    hittable_list(){

    }
    hittable_list(shared_ptr<hittable> object)
    {
        add(object);
    }

    void add(shared_ptr<hittable> obj)
    {
        objects.push_back(obj);
        bbox = aabb(bbox, obj->bounding_box());
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record tmp;
        bool hit_any = false;
        auto closest_hit = ray_t.max;

        for (const auto& object : objects)
        {
            if(object->hit(r, interval(ray_t.min, closest_hit), tmp))
            {
                hit_any = true;
                closest_hit = tmp.t;
                rec = tmp;
            }
        }

        return hit_any;



    }

    aabb bounding_box() const override { return bbox;}

private:
    aabb bbox;

};
#endif //RAYTRACER_HITTABLE_LIST_H
