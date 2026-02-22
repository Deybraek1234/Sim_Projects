#include <Eigen/Core>
#include "particle.h"

void time_step_forward(Particle& sun, Particle& planet) {
    planet.position += planet.velocity * dt + 0.5f * planet.acceleration * dt * dt;
    sun.position += sun.velocity * dt + 0.5f * sun.acceleration * dt * dt;

    vec2 old_p1_acceleration = planet.acceleration;
    vec2 old_sun_acceleration = sun.acceleration;

    vec2 r_vector = sun.position - planet.position;

    float distance_squared = r_vector.squaredNorm();

    if(distance_squared > 0.01f) {
        float force_mag = (G * sun.mass * planet.mass) / distance_squared;
        vec2 force_vec = r_vector.normalized() * force_mag;

        planet.acceleration = force_vec / planet.mass;
        sun.acceleration = -force_vec / sun.mass;
    };

    planet.velocity += 0.5f * (old_p1_acceleration + planet.acceleration) * dt;
    sun.velocity += 0.5f * (old_sun_acceleration + sun.acceleration) * dt;
}