#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <sstream>
#include <vector>
#include <random>
#include "collision.h"

typedef std::vector<double> vec;

class Particle{
    public:
        vec position_x;
        vec position_y;
        vec velocity_x;
        vec velocity_y;
        vec acceleration_x;
        vec acceleration_y;
        vec mass;
            
};

//definitions
const double dt = 0.005;

//limits 
int window_width1 = 1920;
int window_height1 = 1080;


int main(){
    bool running = true;

    //window setup
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Renderer* text;
    SDL_Init(SDL_INIT_VIDEO);
    bool result_renderer = SDL_CreateWindowAndRenderer("Sim", window_width1, window_height1,0, &window, &renderer);
    if (!result_renderer) {
        std::cout << "Failed to create window and renderer: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_SetRenderLogicalPresentation(renderer, window_width1, window_height1, SDL_LOGICAL_PRESENTATION_STRETCH);
    if(TTF_Init() == -1){
        std::cout <<"Failed to initialize text"<<std::endl;
    }
    TTF_Font* font = TTF_OpenFont("AdwaitaSans-Regular.ttf", 24);    

    //define and initialize things needed
    double total_time = 0;
    int n_particles=1;
    std::cout << "How many particles?";
    std::cin >> n_particles;

    Particle particle;

    std::random_device rd1;
    std::mt19937 gen(rd1());
    std::uniform_real_distribution<> distribx(0.0,(double)window_width1);
    std::uniform_real_distribution<> distriby(0.0,(double)window_height1);
    SDL_FPoint screen_points[n_particles];
    double temp_pos_x, temp_pos_y;

    for(int i=0;i<n_particles;i++){
        particle.position_x.push_back(temp_pos_x = distribx(gen));
        particle.position_y.push_back(temp_pos_y = distriby(gen));

        particle.velocity_x.push_back(0.0);
        particle.velocity_y.push_back(0.0);
        particle.mass.push_back(1.0);

        particle.acceleration_x.push_back(0.0);
        particle.acceleration_y.push_back(9.81);
    };

    //main loop
    while(running){

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
            for(int i=0; i<n_particles; i++){                
                double a_curr_x = 0;
                double a_curr_y = -9.81;

                particle.position_x[i] += particle.velocity_x[i]*dt + 0.5*a_curr_x*dt*dt;
                particle.position_y[i] += particle.velocity_y[i]*dt + 0.5*a_curr_y*dt*dt;

                double a_new_x =0.0;
                double a_new_y=-9.81;                

                particle.velocity_x[i] += 0.5*(a_curr_x + a_new_x)*dt;
                particle.velocity_y[i] += 0.5*(a_curr_y + a_new_y)*dt;
            };
            collision_detection(particle.position_x, particle.position_y, particle.velocity_x, particle.velocity_y, n_particles);

 
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            for(int i=0; i<n_particles; i++){
                screen_points[i] = { (float)(particle.position_x[i]+ (double)(window_height1)/2) , (float)(-1*(particle.position_y[i]-(double)window_height1+1)) };
            };
            SDL_RenderPoints(renderer, screen_points, n_particles);


            //text
            std::stringstream ss;
            ss << total_time << "s";
            std::string time_string = ss.str();
            SDL_Color textColor = {255, 255, 255, 255};

            SDL_Surface* textSurface = TTF_RenderText_Solid(font, time_string.c_str(), time_string.size(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            float textW = textSurface->w;
            float textH = textSurface->h;
            SDL_DestroySurface(textSurface);
            SDL_FRect rect = {float(window_width1-textW - 10), 10.f, textW, textH};
            SDL_RenderTexture(renderer, textTexture, NULL, &rect);
            SDL_DestroyTexture(textTexture);
            SDL_RenderPresent(renderer);

            //increment time
            total_time += dt;
    };
};

