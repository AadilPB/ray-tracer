#include "raytracer.h"

#include "bvh.h"
#include "camera.h"
#include "constant_medium.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "quad.h"
#include "tri.h"
#include "thread_pool.h"
#include "renderer.h"
#include "texture.h"
#include "scene_reader.h"

#include <chrono>
#include <vector>
#include <mutex>




void read_json(const char* path, bool multithreaded)
{
    hittable_list world;
    camera cam;

    scene_reader::load_scene(path, cam, world);

    world = hittable_list(make_shared<bvh_node>(world));
    
    if(multithreaded == false)
    {
        renderer render(cam, world, 1);
        render.scanline_render();  
    }
    else
    {
        renderer render(cam, world);
        render.scanline_render();
    }
        
}

int main(int argc, char* argv[]) 
{
   bool multithreaded = true;
   if(argc > 2 && std::string(argv[2]) == "-single")
   {
        multithreaded = false;
   }

   read_json(argv[1], multithreaded);    
        
    
    
}

