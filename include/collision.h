#ifndef collisions_h
#define collisions_h
#include<vector>

typedef std::vector<double> vec;

void collision_detection(vec& position_x, vec& position_y, vec& velocity_x, vec& velocity_y, int n_particles);

#endif
