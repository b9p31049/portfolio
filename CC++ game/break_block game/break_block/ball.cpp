#include "sys.h"
#include "ball.h"

//初期化
void Ball::init(){
  using namespace sys;
  px = get_screen_w() / 2;	//初期位置x
  py = get_screen_h() / 2;	//初期位置y
  dx = 0.5;					//初期進行方向x
  dy = 0.5;					//初期進行方向y
  speed = 0.5;				//速度
  text = "*";					//文字列
}

  //モデル
void Ball::model(){
  px = get_next_x();	//位置更新x
  py = get_next_y();	//位置更新y
}

//ヴュー
void Ball::view(){
  using namespace sys;
  if( py < get_screen_h() ){
	set_style( COL_CYAN, COL_BLUE, STYLE_NORMAL );
	print( px, py, text );
	reset_style();
  }
}

//次のフレームの位置
double Ball::get_next_x(){	return px + dx * speed; }
double Ball::get_next_y(){	return py + dy * speed; }

//進行方向反射
void Ball::reflect_x(){ dx *= -1.0; }
void Ball::reflect_y(){ dy *= -1.0; }

//パドルにあたった位置に応じて進行方向を少しずらす。
void Ball::change_dir( double rate ){
  dx = rate;
  //進行方向ベクトルを長さ１に正規化
  double len = sqrt( dx * dx + dy * dy );
  dx /= len;
  dy /= len;
}

