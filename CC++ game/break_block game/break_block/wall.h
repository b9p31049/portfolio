#pragma once

#include "mvcobject.h"
#include "sys.h"

class Wall : public MVCObject{
public:
  bool is_top_wall_hit( double px, double py );
  bool is_btm_wall_hit( double px, double py );
  bool is_left_wall_hit( double px, double py );
  bool is_right_wall_hit( double px, double py );
};

