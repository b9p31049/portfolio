#pragma once

#include "mvcobject.h"
#include <string>

//パドル
class Paddle : public MVCObject{
public:
  double px,py;
  std::string text;
  double width;

  //初期化
  void init();

  //コントローラー
  void controller();

  //ヴュ-
  void view();

  //ボールとの当たり判定
  bool is_hit( double bx, double by);

  //ボールがあたった位置に応じて、
  //-1.0(左端)～1.0(右端)を返す。
  double get_rate( double bx, double by );

};

