#pragma once
#include <string>
#include "mvcobject.h"

//ボール
class Ball : public MVCObject{
public:
  double px,py;
  double dx,dy;
  double speed;
  std::string text;

  //初期化
  void init();

  //モデル
  void model();

  //ヴュー
  void view();

  //次のフレームの位置
  double get_next_x();
  double get_next_y();

  //進行方向反射
  void reflect_x();
  void reflect_y();

  //パドルにあたった位置に応じて進行方向を少しずらす。
  void change_dir( double rate );
};

