#include <iostream>
#include "Color.h"
#include "vec3.h"
#include "ray.h"
#include <fstream>
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
using namespace std;


color ray_color(const ray& r, const hittable& world)
{
    const double infinity = std::numeric_limits<double>::infinity();
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_dir = unit_vector(r.direction());
    auto a = 0.5 *( unit_dir.y() + 1.0);

    // returns a linear interp from white to blue if nothing is hit
    return (1.0 - a)* color(1.0,1.0,1.0) + a*color(0.5, 0.7,1.0);
}
int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    // sets image height cant be less than 1
    image_height = (image_height < 1) ? 1 : image_height;


    // world
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

   //Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * double(image_width)/image_height;
    auto camera_center = point3(0,0,0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                               - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    std :: cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; ++j)
    {
        clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = (pixel_center - camera_center);
            ray r(camera_center, ray_direction);
            color pcolor = ray_color(r, world);
            //auto Colors = color(double(i) / (image_width -1),double(j) / (image_height - 1), 0);
            write_color(cout, pcolor);



        }
    }
    clog << "\rDone.                 \n";
}

// checks if given ray r it hits sphere

