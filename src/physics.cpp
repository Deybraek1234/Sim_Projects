#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <Eigen/Core>
#include "particle.h"
#include "collision.h"
#include "window.h"

//definitions
const double dt = 0.01;
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
    sun.position = {0.0f, 0.0f};
    sun.velocity = {0.0f, -0.1f};
    sun.radius = 6.957e8f;
    sun.mass = 2.0e29f;
    sun.color = {255, 165, 0, 255};
    
    Particle planet1;
    planet1.position = {1.5e10f, 0.0f};
    planet1.velocity = {0.0, 30000.0f};
    planet1.radius = 1.0e8f;
    planet1.mass = 2.0e24;
    planet1.color = {51, 153, 255, 255};
  
    //initialize accelerations
    vec2 r_init = sun.position - planet1.position;
    float dist_sq_init = r_init.squaredNorm();
    float f_mag_init = (G*sun.mass*planet1.mass) / dist_sq_init;
    vec2 f_vec_init = r_init.normalized() * f_mag_init;

    planet1.acceleration = f_vec_init / planet1.mass;
    sun.acceleration = -f_vec_init / sun.mass;
    //main loop
    while(running){
        Uint64 new_time = SDL_GetTicks();
        double frame_time = (new_time - current_time)/1000.0;;
        current_time = new_time;

        if(frame_time > 0.25) frame_time = 0.25;
        double timescale = 20000.0;
        accumulator += frame_time * timescale;

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
            planet1.position += planet1.velocity * dt + 0.5f * planet1.acceleration * dt * dt;
            sun.position += sun.velocity * dt + 0.5f * sun.acceleration * dt * dt;

            vec2 old_p1_acceleration = planet1.acceleration;
            vec2 old_sun_acceleration = sun.acceleration;
            
            vec2 r_vector = sun.position - planet1.position;

            float distance_squared = r_vector.squaredNorm();
            
            if(distance_squared > 0.01f) {
                float force_mag = (G * sun.mass * planet1.mass) / distance_squared;
                vec2 force_vec = r_vector.normalized() * force_mag;

                planet1.acceleration = force_vec / planet1.mass;
                sun.acceleration = -force_vec / sun.mass;
            };

            planet1.velocity += 0.5f * (old_p1_acceleration + planet1.acceleration) * dt;
            sun.velocity += 0.5f * (old_sun_acceleration + sun.acceleration) * dt;

            //increment time
            total_time += dt;
            accumulator -= dt;
        }
        
        refresh_window(renderer);
        draw_circle(renderer, sun, sun.color);
        draw_circle(renderer, planet1, planet1.color);

        //text
        std::stringstream ss;
        ss << total_time/60 << "m";
        std::string time_string = ss.str();
        SDL_Color textColor = {255, 255, 255, 255};

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, time_string.c_str(), time_string.size(), textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        float textW = textSurface->w;
        float textH = textSurface->h;

        destroy_window(renderer, textSurface, textTexture, textW, textH);
    };
};