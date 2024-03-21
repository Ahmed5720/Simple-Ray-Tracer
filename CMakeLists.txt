cmake_minimum_required(VERSION 3.27)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer main.cpp
        Color.h
        vec3.h
        ray.h
        hittable.h
        sphere.h
        hittable_list.h
)
