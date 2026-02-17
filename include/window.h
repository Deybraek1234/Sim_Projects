#ifndef window_h
#define window_h
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include "particle.h"

bool init_window(SDL_Window*& window, SDL_Renderer*& renderer);

bool set_font(SDL_Renderer*& renderer);

void draw_particle(SDL_Renderer*& renderer, const Particle& particle);

void refresh_window(SDL_Renderer*& renderer);

void destroy_window(SDL_Renderer*& renderer, SDL_Surface*& textSurface, SDL_Texture*& textTexture, float textW, float textH);

void draw_circle(SDL_Renderer*& renderer, const Particle& planet, SDL_Color color);

struct Screen {int width; int height;};
extern Screen screen;
#endif