#ifndef RENDERER_H
#define RENDERER_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "camera.h"
#include "hittable_list.h"
#include "thread_pool.h"


#include <chrono>
#include <vector>
#include <mutex>

using namespace std::chrono;

class renderer
{
    public:
        
        renderer(camera cam, hittable_list world) 
        : cam(cam), world(world)  
        {
            cam.initialize();
            win = window(cam.image_width, cam.image_height);
            image_data = std::vector<uint8_t>(cam.image_height * cam.image_width * 3, 0);
            
        }

        renderer(camera cam, hittable_list world, int num_threads) 
        : cam(cam), world(world), pool(num_threads)  
        {
            cam.initialize();
            win = window(cam.image_width, cam.image_height);
            image_data = std::vector<uint8_t>(cam.image_height * cam.image_width * 3, 0);
            
        }

        void scanline_render()
        {
            auto start = std::chrono::steady_clock::now();
    
            futures.clear();
            cam.initialize();
            win.open_window();
            
            std::atomic<int> completed = 0;
            std::atomic<bool> quit = false; 

            std::mutex scanline_count_mutex;
            
            for (int j = 0; j < cam.image_height; j++)
            {
                
                futures.push_back(pool.enqueue([&, j]() mutable{
                    if (quit == 1) return; 
                    
                    cam.render_scanline(world, j, image_data);
                    completed++;
                    {
                        std::lock_guard<std::mutex> lock(scanline_count_mutex);
                        std::clog << "\rScanlines remaining: " << (cam.image_height - completed) << ' ' << std::flush; 
                    }
                }));     
            }

            for (auto& f : futures)
            {
                f.get();
                win.update_display(image_data);
                
                if(win.process_event() == false)
                {
                    quit = true;
                    break;
                }
                
            }

            auto end = std::chrono::steady_clock::now();

            auto elapsed = end - start;

            std::clog << "Elapsed time: "  << duration_cast<milliseconds>(elapsed).count() << " ms";
            stbi_write_png("renders/image.png", cam.image_width, cam.image_height, 3, image_data.data(), cam.image_width * 3);
            std::clog << "\rDone.                 \n";

            win.poll_event();
        }
     

        void tile_render()
        {
            auto start = std::chrono::steady_clock::now();
    
            futures.clear();
            cam.initialize();
              
            win.open_window();
            
            std::atomic<int> cur_tiles = 0;
            std::atomic<bool> quit = false; 

            int tiles = (cam.image_height + 31) / 32 * (cam.image_width + 31)/32; 

            std::mutex tile_count_mutex;
            
            for (int j = 0; j < cam.image_height; j += 32)
            {
                for(int i = 0; i < cam.image_width; i += 32)
                {
                    futures.push_back(pool.enqueue([&, i, j]() mutable{
                        if (quit == 1) return; 
                        cam.render_tile(world, i, j, image_data);
                        cur_tiles++;            
                        {
                            std::lock_guard<std::mutex> lock(tile_count_mutex);
                            std::clog << "\rTiles remaining: " << (tiles - cur_tiles) << ' ' << std::flush; 
                        }
                    })); 
                }          
            }

            for (auto& f : futures)
            {
                f.get();
                win.update_display(image_data);
                if(win.process_event() == false)
                {
                    quit = true;
                    break;
                }
                
            }

            auto end = std::chrono::steady_clock::now();

            auto elapsed = end - start;
            std::clog << "\rDone.                 \n";
            std::clog << "Elapsed time: "  << duration_cast<milliseconds>(elapsed).count() << " ms";
            
            stbi_write_png("image.png", cam.image_width, cam.image_height, 3, image_data.data(), cam.image_width * 3);
            

            win.poll_event();
        }

    private:
        camera cam;
        hittable_list world;
        thread_pool pool;
        std::vector<uint8_t>  image_data;
        std::vector<std::future<void>> futures;
        window win;
        

};


#endif
