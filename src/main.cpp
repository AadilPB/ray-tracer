#include "raytracer.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "thread_pool.h"

#include <chrono>
#include <vector>
#include <mutex>

using namespace std::chrono;


int main() 
{
    hittable_list world;


    auto ground_material =  make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9 * random_double());

            if((center - point3(4, 0.2, 0)).length() > 0.9)
            {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 5;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13, 2,  3);
    cam.lookat   = point3( 0, 0, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle =  0.6;
    cam.focus_dist    = 10.0;

    
    
    auto start = std::chrono::steady_clock::now();
    
    cam.initialize();
    
    std::vector<uint8_t> image_data(cam.image_height * cam.image_width * 3, 0);
    
    
    window win(cam.image_width, cam.image_height);
    
    win.open_window();
    /*
    std::vector<std::future<void>> futures;
    
    thread_pool pool;
    
    std::atomic<int> completed = 0;

    std::mutex scanline_count_mutex;
    std::mutex window_mutex;*/
    /*
    for (int j = 0; j < cam.image_height; j++)
    {
           
        futures.push_back(pool.enqueue([&, j]() mutable{
            cam.render_scanline(world, j, image_data);
            completed++;
            {
                std::lock_guard<std::mutex> lock(scanline_count_mutex);
                std::clog << "\rScanline remaining: " << (cam.image_height - completed) << ' ' << std::flush; 
            }
             
            {
                std::lock_guard<std::mutex> lock(scanline_count_mutex);
                
                win.update_display(image_data);
                
            }
        }));     
    }

    for (auto& f : futures)
    {
        f.get();
        if(win.process_event() == false)
        {
            break;
        }
        
    }*/
    
    int tiles = (cam.image_height + 31) / 32 * (cam.image_height + 31)/32; 
    int cur_tiles = 0;
    for(int j = 0; j < cam.image_height; j += 32)
    {
        
        for(int i = 0; i < cam.image_width; i += 32)
        {
            std::clog << "\rTiles remaining: " << tiles - cur_tiles << ' ' << std::flush;
            cam.render_tile(world, i, j, image_data);
            cur_tiles++;
            win.update_display(image_data);
                    
            
        }
        if(win.process_event() == false)
        {
            break;
        }
       
    }

    auto end = std::chrono::steady_clock::now();

    auto elapsed = end - start;

    std::clog << "Elapsed time: "  << duration_cast<milliseconds>(elapsed).count() << " ms";
    
    stbi_write_png("image.png", cam.image_width, cam.image_height, 3, image_data.data(), cam.image_width * 3);
    std::clog << "\rDone.                 \n";

    win.poll_event();
    

 
   


}

