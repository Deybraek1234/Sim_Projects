#include "collision.h"

typedef std::vector<double> vec;
int window_width = 1920;
int window_height = 1080;
const int x_limit_left = -(window_width/2);
const int x_limit_right = window_width/2;
const int y_limit_low = 0;
const int y_limit_high = window_height;
void collision_detection(vec& position_x, vec& position_y, vec& velocity_x, vec& velocity_y, int n_particles){

      for(int i=0;i<n_particles;i++){
            if(position_x[i] < x_limit_left){
                  position_x[i] = x_limit_left;
                  velocity_x[i] = -1*velocity_x[i]*0.9;
            };

            if(position_x[i] > x_limit_right){
                  position_x[i] = x_limit_right;
                  velocity_x[i] = -1*velocity_x[i]*0.9;
            };

            if(position_y[i] < y_limit_low){
                  position_y[i] = y_limit_low;
                  velocity_y[i] = -1*velocity_y[i]*0.9;
            };

            if(position_y[i] > y_limit_high){
                  position_y[i] = y_limit_high;
                  velocity_y[i] = -1*velocity_y[i]*0.9;
            };
      }

}