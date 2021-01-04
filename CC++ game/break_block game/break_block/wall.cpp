#include "wall.h"

bool Wall::is_top_wall_hit( double px, double py ){
  return py < 0;
}
bool Wall::is_btm_wall_hit( double px, double py ){
  return py >= sys::get_screen_h();
}
bool Wall::is_left_wall_hit( double px, double py ){
  return px < 0;
}
bool Wall::is_right_wall_hit( double px, double py ){
  return px >= sys::get_screen_w();
}
