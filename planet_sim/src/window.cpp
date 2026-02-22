#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "particle.h"
#include "window.h"

bool init_window(SDL_Window*& window, SDL_Renderer*& renderer){
    SDL_Init(SDL_INIT_VIDEO);

    bool window_result = SDL_CreateWindowAndRenderer("Sim", screen.width, screen.height, 0, &window, &renderer);
    if (!window_result){
        std::cout << "Failed to create window and renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

bool set_font(SDL_Renderer*& renderer){
    SDL_SetRenderLogicalPresentation(renderer, screen.width, screen.height, SDL_LOGICAL_PRESENTATION_STRETCH);

    if(TTF_Init() == -1){
        std::cout << "Failed to initialize text" << std::endl;
        return false;
    }

    return true;
}

void draw_particle(SDL_Renderer*& renderer, const Particle& particle){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderPoint(renderer, particle.position.x(), particle.position.y());
}

void refresh_window(SDL_Renderer*& renderer){
    SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    SDL_RenderClear(renderer);
};

void destroy_window(SDL_Renderer*& renderer, SDL_Surface*& textSurface, SDL_Texture*& textTexture, float textW, float textH){
    SDL_DestroySurface(textSurface);
    SDL_FRect rect = {float(screen.width - textW - 10), 10.f, textW, textH};
    SDL_RenderTexture(renderer, textTexture, NULL, &rect);
    SDL_DestroyTexture(textTexture);
    SDL_RenderPresent(renderer);
}

void draw_circle(SDL_Renderer*& renderer, const Particle& planet, SDL_Color color){
    int radius_pixels = (int)(planet.radius*scale_factor);
    SDL_SetRenderDrawColor(renderer, planet.color.r, planet.color.g, planet.color.b, planet.color.a);

    for (int w = -radius_pixels; w <= radius_pixels; w++){
        for(int h = -radius_pixels; h <=radius_pixels; h++){
            if(w*w + h*h <= radius_pixels*radius_pixels){
                SDL_RenderPoint(renderer, int(planet.position.x()*scale_factor + screen.width/2 + w), int(planet.position.y()*scale_factor + screen.height/2 + h));
            }
        }
    }
}
