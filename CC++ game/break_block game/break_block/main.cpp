#include "sys.h"

#include <vector>
#include "paddle.h"
#include "wall.h"
#include "ball.h"
#include "block.h"

class Game : MVCObject{
public:

  enum {
	STATE_GAME_TITLE,		//@kadai ENTERキーが押されるのを待つ。
	STATE_GAME_START,		//@kadai ゲームスタート表示３秒。
	STATE_GAME_NOW,
	STATE_GAME_OVER
  };

  int state;				//@kadai 追加
  int game_start_counter;	//@kadai ゲームスタート表示３秒

  int frame_counter;
  double game_over_line;
  Paddle paddle;
  Ball ball;
  Wall wall;
  std::vector< Block > blocks;

  //初期化
  void init(){
	state = STATE_GAME_TITLE;  
	frame_counter = 0;			//フレーム数カウンタ。
	game_over_line =
	  sys::get_screen_h() + 5;	//ゲームオーバーライン
	ball.init();					//ball初期化
	paddle.init();				//paddle初期化
	
	std::string block_text = "[    ]";
	int block_array_x = 8;
	int block_array_y = 4;
	int block_start_x = (sys::get_screen_w() - block_array_x * block_text.size())/2;
	int block_start_y = 4;
	for( int x = 0; x < block_array_x; ++x ){
	  for( int y = 0; y < block_array_y; ++y ){
		int bx = block_start_x + x * block_text.size();
		int by = block_start_y + y;
		int fc = sys::COL_BLACK;
		int bc = (x + y%2) % 2 ? sys::COL_GREEN : sys::COL_YELLOW;
		blocks.push_back( Block( bx,by, block_text, fc, bc ) );
	  }
	}
  }

  //モデル
  void model(){

	double bx = ball.get_next_x();//仮のボール位置
	double by = ball.get_next_y();

	switch( state ){
	case STATE_GAME_TITLE:	//@kadai 
	  if( sys::is_key_pressed() ){	//何かキーが押されていたら
		game_start_counter = sys::fps * 3;		//3秒を数えるカウンタ
		state = STATE_GAME_START;	//GAME_STARTへ
	  }
	  break;
	case STATE_GAME_START:	//@kadai
	  if( game_start_counter-- < 0 ){	//3秒たったら
		state = STATE_GAME_NOW;	//GAME_NOWへ
	  }
	  break;  

	case STATE_GAME_NOW: //@Kadai

		//ボールと壁の当たり判定
		if( wall.is_top_wall_hit( bx, by ) ){
		ball.reflect_y();	//進行方向上下反転
		}else if( wall.is_left_wall_hit( bx, by ) ||
				wall.is_right_wall_hit( bx, by ) ){
		ball.reflect_x();	//進行方向左右反転
		}
		//ボールとパドルの当たり判定
		else if( paddle.is_hit( bx, by ) ){
		ball.change_dir( paddle.get_rate( bx, by ) );
		ball.reflect_y();
		}
		//ボールとブロックの当たり判定
		else{
		for( int i=0; i<blocks.size(); ++i ){
			if( blocks[ i ].is_alive() ){
			if( blocks[ i ].is_horizontal_hit( bx,by ) ){
				ball.reflect_x();	//進行方向左右反転
				blocks[ i ].kill();	//ブロック消去
			}else if( blocks[ i ].is_vertical_hit( bx,by ) ){
				ball.reflect_y();	//進行方向上下反転
				blocks[ i ].kill();	//ブロック消去
			}
			}
		}		
	}
		ball.model();
  
		frame_counter += 1;//フレームカウンタ更新
		
		if(game_over_line < ball.py){
			state = STATE_GAME_OVER;
		}
	break;

	case STATE_GAME_OVER:
		if( sys::is_key_pressed() ){	//何かキーが押されていたら
		for( int i=0; i<blocks.size(); ++i ){
				blocks[ i ].kill();	//ブロック消去
			}

		init();
	  }
	break;
	default:
	  break;
	}
	}

	

  //コントローラー
  void controller(){
	paddle.controller();
  }

  //ヴュー
  void view(){

	//@kadai 状態に応じて情報を表示
	using namespace sys;
	switch( state ){
	case STATE_GAME_TITLE:
	  print( 0,9, "                 " );
	  print( 0,10, "---   break_block  ---" );
	  print( 0,11, "                 " );
	  print( 0,12, "   Push any key  " );
	break;
	case STATE_GAME_START:
	  print( 0,9, "                 " );
	  print( 0,10, "----Get Ready!!--" );
	  print( 0,11, "                 " );
	  print( 0,12, format( "       %d        " , 1 + game_start_counter / sys::fps ) );
	break;

	case STATE_GAME_NOW:
		ball.view();
		paddle.view();
		for( int i=0; i<blocks.size(); ++i ){
		blocks[ i ].view();
		}
	break;

	case STATE_GAME_OVER:
	  print( 0,9, "                 " );
	  print( 0,10, "---- GAME OVER --" );
	  print( 0,11, "                 " );
	break;
	}

  }

  bool is_game_over(){
	//ESCキーが押されるか、もしくは画面下に落ちたら
	//return game_over_line < ball.py || sys::is_escape();
	return sys::is_escape();
  }
};

Game game;

void initialize(){
  //スクリーン初期化
  sys::init();
  sys::display_cursor( false );
  //Game変数の初期化
  game.init();
}

void update(){
  //スクリーン更新
  sys::update();
  //コントローラー
  game.controller();
  //モデル
  game.model();
}

void draw(){
  //画面消去
  sys::erase_screen();
  //ヴュー
  game.view();
  //画面描画
  sys::draw();
}

void kill(){
  sys::exit();
}

int main( int ac, char *av[] )
{
  //初期化
  initialize();

  //無限ループ
  while( ! game.is_game_over() ){
	//更新
	update();

	//描画
	draw();
  }

  //終了
  kill();
  return 0;
}
