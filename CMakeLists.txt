cmake_minimum_required(VERSION 3.27)

# The toolchain file setup should ideally be in a CMakePresets.json file,
# but we'll keep it here for simplicity
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")
    
project(RayTracer)


find_package(OpenGL REQUIRED)
find_package(OpenMP REQUIRED)
add_executable(RayTracer main.cpp
        Color.h
        vec3.h
        ray.h
        hittable.h
        sphere.h
        hittable_list.h
        Interval.h
        camera.h
        aabb.h
        bvh.h
        common.h
        material.h

        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)




# Add the path to vcpkg installed include and lib folders
target_include_directories(RayTracer PRIVATE
    ${CMAKE_SOURCE_DIR}/glew/include
    ${CMAKE_SOURCE_DIR}/glfw/include
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

target_link_directories(RayTracer PRIVATE
        ${CMAKE_SOURCE_DIR}/glew/lib/Release/x64
    ${CMAKE_SOURCE_DIR}/glfw/lib-vc2022
)

target_link_libraries(RayTracer PRIVATE
    glfw3
    glew32s
    OpenGL::GL
    OpenMP::OpenMP_CXX
    
)

target_compile_features(RayTracer PRIVATE cxx_std_17)
target_compile_definitions(RayTracer PRIVATE GLEW_STATIC)