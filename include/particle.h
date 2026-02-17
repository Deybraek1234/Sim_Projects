#pragma once
#include <Eigen/Core>
#include <SDL3/SDL.h>

typedef Eigen::Vector2f vec2;

class Particle {
public:
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float radius;
    float mass;
    SDL_Color color;

    Particle() {
        position = {0, 0};
        velocity.setZero();
        acceleration.setZero();
        radius = 0.1f;
        mass = 1.0f;
        color = {255, 255, 255, 255};
    }
};

const float PPM = 3e-8f;
const float G = 6.674e-11f;