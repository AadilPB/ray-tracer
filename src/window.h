#ifndef WINDOW_H
#define WINDOW_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

class window
{


    public:
        double width;
        double height;

        void open_window()
        {
            if(SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                std::cerr << "Failed to initialize the SDL2 library\n";
            }

            window = SDL_CreateWindow("SDL2 Window",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                680, 480,
                                                0);

            if (!window)
            {
                std::cerr << "Failed to create window\n";
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, height, width);

            
        
        }

        void update_display()
        {
           
        }


    private:
        SDL_Window *window; 
        SDL_Renderer *renderer;
        SDL_Texture *texture;
};

#endif
