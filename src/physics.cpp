#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <Eigen/Core>
#include "particle.h"
#include "collision.h"
#include "window.h"

//definitions
const double dt = 0.002;
Screen screen = {1920, 1080};

int main(){
    bool running = true;

    //initialize SDL pointers
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Renderer* text;

    init_window(window, renderer);
    set_font(text);
    
    //initialize font
    TTF_Font* font = TTF_OpenFont("font.ttf", 24);

    //define and initialize things needed
    Uint64 current_time = SDL_GetTicks();
    double accumulator = 0.0;
    double total_time = 0.0;

   Particle sun;
   sun.radius = 6.0f;
   sun.mass = 1.9891E2;
   
    //main loop
    while(running){
        Uint64 new_time = SDL_GetTicks();
        double frame_time = (new_time - current_time) / 1000.0;
        current_time = new_time;

        if(frame_time > 0.25) frame_time = 0.25;
        accumulator += frame_time;

        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    if(event.key.key == SDLK_ESCAPE){
                        running = false;
                    }
                break;
            }
        }

        while (accumulator >= dt) {
            vec2 a_curr = {0.0, 0};
            sun.position += sun.velocity*dt + 0.5*a_curr*dt*dt;
            vec2 a_new = {0.0, 0};
            sun.velocity += 0.5*(a_curr + a_new)*dt;
        
            //increment time
            total_time += dt;
            accumulator -= dt;
        }
        refresh_window(renderer);
        draw_circle(renderer, sun);
        Particle particle;
        draw_particle(renderer, particle);

        //text
        std::stringstream ss;
        ss << total_time << "s";
        std::string time_string = ss.str();
        SDL_Color textColor = {255, 255, 255, 255};

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, time_string.c_str(), time_string.size(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        float textW = textSurface->w;
        float textH = textSurface->h;

        destroy_window(renderer, textSurface, textTexture, textW, textH);
    };
};

