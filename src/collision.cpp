#include "particle.h"
#include "window.h"
#include <Eigen/Core>

typedef Eigen::Vector2f vec2;

void wall_collision_check(Particle& particle){
      vec2 screen_bounds = {screen.width/PPM, screen.height/PPM};

      auto hit_low = particle.position.array() < 0;
      auto hit_high = particle.position.array() > screen_bounds.array();

      float damping = 0.95f;

      vec2 flip_factors = (hit_low || hit_high).select(
            Eigen::Vector2f::Constant(-damping), 
            Eigen::Vector2f::Constant(1.0f)
      );
      particle.velocity = particle.velocity.cwiseProduct(flip_factors);
      particle.position = particle.position.cwiseMax(0).cwiseMin(screen_bounds);
}