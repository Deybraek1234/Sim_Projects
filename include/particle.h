#pragma once
#include <Eigen/Core>

typedef Eigen::Vector2f vec2;

class Particle {
public:
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    float radius;
    float mass;

    Particle() {
        position = {500, 500};
        velocity.setZero();
        acceleration.setZero();
        radius = 1.0f;
        mass = 1.0f;
    }
};

const float PPM = 100.0f;