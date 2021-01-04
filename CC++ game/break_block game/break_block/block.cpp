#include "block.h"
#include "sys.h"

Block::Block( double x, double y, std::string t, int f, int b ){
  px = x;				//位置x
  py = y;				//位置y
  text = t;				//表示文字列
  width = text.size();	//文字列の長さ
  alive = true;			//生存フラグ
  fore_color = f;		//文字色
  back_color = b;		//文字背景色
}

//ヴュー
void Block::view(){
  using namespace sys;
  if( alive ){
	set_style( fore_color, back_color, STYLE_NORMAL );
	print( px, py, text );
	reset_style();
  }
}
  
//生存確認
bool Block::is_alive(){
  return alive;
}
  
//死亡フラグを立てる
void Block::kill(){
  alive = false;
}
  
//ボールとの当たり判定
bool Block::is_horizontal_hit( double bx, double by ){
  return (int)by == (int)py && ((int)bx == (int)px || (int)bx == (int)(px+width));
}
bool Block::is_vertical_hit( double bx, double by ){
  return is_top_hit( bx, by ) || is_btm_hit( bx, by );
}
bool Block::is_top_hit( double bx, double by ){
  return (int)by == (int)(py-1) && bx >= px && bx <= (px+width);
}
bool Block::is_btm_hit( double bx, double by ){
  return (int)by == (int)(py+1) && bx >= px && bx <= (px+width);
}
