#include "raytracer.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <chrono>

using namespace std::chrono;


int main() 
{
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    auto start = std::chrono::steady_clock::now();

    cam.render(world);

    auto end = std::chrono::steady_clock::now();

    auto elapsed = end - start;

    std::clog << "Elapsed time: "  << duration_cast<milliseconds>(elapsed).count() << " ms";
   

}

