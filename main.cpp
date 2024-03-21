
#include "vec3.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
using namespace std;



int main() {


    // world
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

   //Camera

   camera camera;

   camera.render(world);


}



