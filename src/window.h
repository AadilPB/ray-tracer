#ifndef WINDOW_H
#define WINDOW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class window
{


    public:
        
        window(int width, int height) : width(width), height(height)
        {} 

      

        void open_window()
        {
            if(SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                std::cerr << "Failed to initialize the SDL2 library\n";
            }

            display = SDL_CreateWindow("Render",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                width, height,
                                                0);

            if (!display)
            {
                std::cerr << "Failed to create window\n";
            }

            renderer = SDL_CreateRenderer(display, -1, 0);
            texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, width, height);

            
        
        }

        void update_display(std::vector<uint8_t> pixels)
        {
           
           SDL_UpdateTexture(texture, nullptr, pixels.data(), width * 3);
           SDL_RenderCopy(renderer, texture, nullptr, nullptr);
           SDL_RenderPresent(renderer);
        
        }

        void poll_event()
        {
            bool isRunning = true;
            SDL_Event ev;

            while(isRunning)
            {
                while(SDL_PollEvent(&ev) != 0)
                {
                    if(ev.type == SDL_QUIT)
                        isRunning = false;
                }
                
            }
        }

        bool process_event()
        {
            SDL_Event ev;
            while(SDL_PollEvent(&ev) != 0)
            {
                if(ev.type == SDL_QUIT)
                    return false;
            }

            return true;
        }


    private:
        SDL_Window *display; 
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        int width;
        int height;
};

#endif
