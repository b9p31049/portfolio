#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#undef MOUSE_MOVED

namespace sys {
  
#include <curses.h>

  extern int COL_RED;
  extern int COL_WHITE;
  extern int COL_BLACK;
  extern int COL_BLUE;
  extern int COL_GREEN;
  extern int COL_CYAN;
  extern int COL_MAGENTA;
  extern int COL_YELLOW;

  extern int STYLE_NORMAL;
  extern int STYLE_BOLD;
  extern int STYLE_UNDERLINE;
  extern int STYLE_BLINK;
  
  extern int fps;
  
  class string_buffer : public std::stringstream{
  public:
	std::string text;
	int style;
	int fore_color;
	int back_color;
	string_buffer( int f = COL_WHITE, int b = COL_BLACK, int s = STYLE_NORMAL ) : std::stringstream(){
	  style = s;
	  fore_color = f;
	  back_color = b;
	}
	string_buffer( const char *s )  : std::stringstream(){
	  style = STYLE_NORMAL;
	  fore_color = COL_WHITE;
	  back_color = COL_BLACK;
	  *this << s;
	}

	void reset(){
	  str() = "";
	  clear(std::stringstream::goodbit);
	}
	virtual ~string_buffer(){
	}
	operator std::string& () {
	  text = str();
	  return text;
	}
	string_buffer& operator = ( const char *s ) {
	  str() = s;
	  return *this;
	}
  };


  typedef enum {
	NONE,
	CLIENT_WAITING,
	SERVER_WAITING,
	CLIENT_CONNECTED,
	SERVER_CONNECTED
  }NETWORK_STATE;
	
  bool start_server();
  bool start_client( std::string ip );
  NETWORK_STATE get_network_state();
  bool has_connection();
  bool kill_connection();
  std::string read_network();
  bool write_network( std::string& buffer );
  std::string get_local_ip();
  
  //初期化処理
  //プログラム起動時に一度だけ呼ぶ。
  extern void init( int fps=60 );
  
  //終了処理
  //プログラム終了時に一度だけ呼ぶ。
  extern void exit();

  //更新処理
  //毎フレーム呼び出す。
  //内部で1/60秒停止する。
  extern void update();

  //画面消去処理
  //毎フレーム呼び出す。
  extern void erase_screen();

  //画面表示処理
  //毎フレーム呼び出す。
  extern void draw();

  //文字描画
  extern int strlen_utf8( std::string &str );
  extern std::string format(const char* format, ...);
  extern void print( int x, int y, std::string &str );
  extern void print( int x, int y, string_buffer &strb );
  extern void print( int x, int y, const char *str );
  extern void print( int x, int y, const char c );

  //文字属性
  extern void set_style( int fore_color, int back_color, int style = STYLE_NORMAL );
  extern void reset_style();
  
  //カーソル表示
  extern void display_cursor( bool flg );
  
  //入力の詳細を文字列で取得。
  extern std::string get_key_info( int key );

  //キーボード入力を取得
  //キーボード入力を取得
  extern bool is_key_trigger( int no );
  extern bool is_key_release( int no );
  extern bool is_key_press( int no );

  extern bool is_up_key_trigger();
  extern bool is_up_key_press();
  extern bool is_up_key_release();
  extern bool is_down_key_trigger();
  extern bool is_down_key_press();
  extern bool is_down_key_release();
  extern bool is_left_key_trigger();
  extern bool is_left_key_press();
  extern bool is_left_key_release();
  extern bool is_right_key_trigger();
  extern bool is_right_key_press();
  extern bool is_right_key_release();
  extern bool is_space_key_trigger();
  extern bool is_space_key_press();
  extern bool is_space_key_release();
  
  extern int get_key();
  extern bool is_key_pressed();
  extern bool get_shift_key();
  extern bool get_ctrl_key();
  extern bool get_alt_key();

  //ESC_KEYが押されたかどうか
  extern bool is_escape();

  //マウスボタン入力を取得
  extern bool is_mouse_pressed( int no = -1 );
  extern bool get_mouse_r();
  extern bool get_mouse_m();
  extern bool get_mouse_l();
  
  //マウス座標を取得
  extern int get_mouse_x();
  extern int get_mouse_y();

  //画面のサイズを取得
  extern int get_screen_w();
  extern int get_screen_h();

  //ビープ音
  extern void play_beep();

  //画面フラッシュ
  extern void flash_screen();

  //乱数 0~maxまでの乱数を返す
  extern int get_rand( int max );

  //ポリモーフィズムを使う場合にはこの配列に収める.
  template < class Base, class BasePtr=Base*, class BaseRef=Base& >
	class polymorph_vector : public std::vector< BasePtr >{
  public:
  typedef std::vector< BasePtr > base;
  void push_back( Base& value ){ base::push_back( &value ); }
  BaseRef operator [] (size_type pos ){ return *base::at( pos ); }
  };
  
}
