#pragma once
#include <string>
#include "mvcobject.h"
#include "sys.h"

class Block : public MVCObject{
public :
  double px,py;
  std::string text;
  double width;
  int fore_color,back_color;
  bool alive;

  //コンストラクタ
  Block( double x, double y, std::string t, int f=sys::COL_BLACK, int b=sys::COL_BLUE );

  //ビュー
  void view();
  
  //生存確認
  bool is_alive();
  
  //死亡フラグを立てる
  void kill();
  
  //ボールとの当たり判定
  bool is_horizontal_hit( double bx, double by );
  bool is_vertical_hit( double bx, double by );
  bool is_top_hit( double bx, double by );
  bool is_btm_hit( double bx, double by );
};
