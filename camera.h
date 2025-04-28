//
// Created by 15854 on 3/21/2024.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "hittable.h"
#include "material.h"
#include <omp.h>
class camera {
public:

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 800; // rendered image width
    int image_height = 600;
    int samples_per_pixel = 10;   // Count of random samples for each pixel
    int max_depth         = 10;   // Maximum number of ray bounces into scene
    double vfov = 90;
    float* framebuffer = nullptr;

    point3 lookfrom = point3(0,0,0);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);
    void render(const hittable &world) {

        initialize();
        framebuffer = new float[image_width * image_height * 3];
        std :: cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        #pragma omp parallel for schedule(dynamic, 1)
        for (int j = 0; j < image_height; ++j)
        {
            //std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0,0,0);
    
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                //auto Colors = color(double(i) / (image_width -1),double(j) / (image_height - 1), 0);
                //write_color(std::cout, pixel_samples_scale * pixel_color);
               
                int index = 3 * (j * image_width + i);
                framebuffer[index + 0] = pixel_samples_scale * pixel_color.x();
                framebuffer[index + 1] = pixel_samples_scale * pixel_color.y();
                framebuffer[index + 2] = pixel_samples_scale * pixel_color.z();


            }
        }
        std::clog << "\rDone.                 \n";
    }

private:

    //int image_height;
    point3 center;
    double pixel_samples_scale;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    vec3 u,v,w; // camera frame bases u = camera's right, camera's up, camera back respectively.

    void initialize() {

        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        auto focal_length = (lookfrom - lookat).length();
        
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w,u);

        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta/2);
        auto viewport_height = 2 * h * focal_length;

        center = lookfrom;
        auto viewport_width = viewport_height * double(image_width) / image_height;
        auto camera_center = point3(0, 0, 0);

        // Calculate the image height, and ensure that it's at least 1.
        image_height = int(image_width / aspect_ratio);
        // sets image height cant be less than 1
        image_height = (image_height < 1) ? 1 : image_height;

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        

        vec3 viewport_u = viewport_width * u;    
        vec3 viewport_v = viewport_height * -v;



        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
       
        auto viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    color ray_color(const ray& r, int depth , const hittable& world)
    {
        const double infinity = std::numeric_limits<double>::infinity();
        if(depth <= 0)
            return color(0,0,0);
        hit_record rec;
        if (world.hit(r, interval(0.001, infinity), rec)) {

            ray scattered;
            color attenuation;

            if(rec.mat->scatter(r, rec, attenuation, scattered))
            {
                return attenuation * ray_color(scattered, depth-1, world);
            }
            return color(0,0,0);
            // goal is to return color after enough bounces
            // we get the ray at the hit, then we get the direction obtained from randomizing the hit normal and using that we create a new ray and pass it into ray color
            //return 0.5 * (rec.normal + color(1,1,1));
            //vec3 direction = random_on_hemisphere(rec.normal); 
            // to achieve true lambertian reflection, the dir shouldnt be random, it should instead be proportional to cos(normal - dir)
            // we get that by drawing a circle on the front face whos center is p + n and we ensure that the new dir lies within it
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);
        }

        vec3 unit_dir = unit_vector(r.direction());
        auto a = 0.5 *( unit_dir.y() + 1.0);

        // returns a linear interp from white to blue if nothing is hit
        return (1.0 - a)* color(1.0,1.0,1.0) + a*color(0.5, 0.7,1.0);
    }

    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }
    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

};
#endif //RAYTRACER_CAMERA_H
