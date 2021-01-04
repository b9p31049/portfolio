#pragma once

#include "paddle.h"
#include "sys.h"

//初期化
void Paddle::init(){
	using namespace sys;
	px = get_screen_w()/2;		//表示位置x
	py = get_screen_h() - 1;	//表示位置y
	text = "-------";			//表示する文字列
	width = text.size();		//文字列の長さ
}

//コントローラー
void Paddle::controller(){
  using namespace sys;
  px = (double)get_mouse_x();			//マウスで移動
  if( px + width >= get_screen_w() )	//画面からはみ出ないように
	px = get_screen_w() - width;
}

//ヴュー
void Paddle::view(){
  using namespace sys;
  set_style( COL_GREEN, COL_CYAN, STYLE_NORMAL );
  print( px, py, text );
  reset_style();
}

//ボールとの当たり判定
bool Paddle::is_hit( double bx, double by){
  return ( (int)by == (int)py && bx >= px && bx <= (px + width) );
}

  //ボールがあたった位置に応じて、
  //-1.0(左端)～1.0(右端)を返す。
double Paddle::get_rate( double bx, double by ){
  double half_width = width / 2;
  return (bx - (px + half_width)) / half_width;
}


