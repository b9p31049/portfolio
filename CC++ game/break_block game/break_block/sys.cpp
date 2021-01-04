#include <winsock2.h>
#include <stdlib.h>
#include <vector>
#include <locale.h>
#include <time.h>
#include <string>
#include <chrono>
#include <thread>
#include <cstdarg>
#include <memory>
#include <iostream>
#include <map>

#undef MOUSE_MOVED
#include "sys.h"
namespace sys{

  int COL_RED = COLOR_RED;
  int COL_WHITE = COLOR_WHITE;
  int COL_BLACK = COLOR_BLACK;
  int COL_BLUE = COLOR_BLUE;
  int COL_GREEN = COLOR_GREEN;;
  int COL_CYAN = COLOR_CYAN;
  int COL_MAGENTA = COLOR_MAGENTA;
  int COL_YELLOW = COLOR_YELLOW;
  int STYLE_NORMAL = A_NORMAL;
  int STYLE_BOLD = A_BOLD;
  int STYLE_UNDERLINE = A_UNDERLINE;
  int STYLE_BLINK = A_BLINK;
  
  int input;
  int input_mod;
  int fps;
  double mspf;
  long last_time;

  std::vector< std::vector<bool> > last_keys;
  //---------------------------------------------------------
  //Utils
  //---------------------------------------------------------
  std::string format(const char* format, ...)
  {
    va_list args;
    va_start(args, format);
#ifndef _MSC_VER
	size_t size = std::snprintf( nullptr, 0, format, args) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf( new char[ size ] ); 
	std::vsnprintf( buf.get(), size, format, args);
	return std::string(buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
#else
	int size = _vscprintf(format, args);
	std::string result(++size, 0);
	vsnprintf_s((char*)result.data(), size, _TRUNCATE, format, args);
	return result;
#endif
    va_end(args);
  }
  
  long get_time() {
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
	auto value = now_ms.time_since_epoch();

	return (long) value.count();
  }
  
  void wait( long msec ){
	long cur_time = get_time();
	long tgt_time = last_time + msec;
	if( tgt_time > cur_time ){
	  std::this_thread::sleep_for(std::chrono::milliseconds(tgt_time - cur_time));
	  cur_time = tgt_time;
	}
	last_time = cur_time;
  }

  
  int get_rand( int max ){
	return rand() % max;
  }
  

  //---------------------------------------------------------
  //ネットワーク
  //---------------------------------------------------------
#define NETWORK_BUFFER_SIZE 512
  volatile static NETWORK_STATE network_state = NETWORK_STATE::NONE;
  volatile static char network_buffer[ NETWORK_BUFFER_SIZE ];
  static std::thread network_thread;
  static SOCKET sock0;
  volatile static SOCKET sock;
  volatile static bool network_kill_request;
  static std::string ip_addr;
  static char ip[ 16 ];

  std::string get_local_ip(){
	return ip_addr;
  	// struct sockaddr_in  sin;
  	// socklen_t len = sizeof(sin);
  	// getpeername(sock, (struct sockaddr*) & sin, &len);
  	// printf("server ip addres: %s\n", inet_ntoa(sin.sin_addr));
  	// return ip.assign( inet_ntoa(sin.sin_addr) );
  }
  void set_local_ip(){
	struct hostent *host_entry;
	char host_name[ 128 ];
	gethostname( host_name, sizeof(host_name));
	host_entry = gethostbyname(host_name); 
	ip_addr.assign( inet_ntoa(*((struct in_addr*) 
								host_entry->h_addr_list[0])) );
  }

  NETWORK_STATE get_network_state(){
	return network_state;
  }
  
  bool has_connection(){
	return
	  network_state == NETWORK_STATE::SERVER_CONNECTED ||
	  network_state == NETWORK_STATE::CLIENT_CONNECTED;
  }
  
  bool kill_connection(){
	//なんもしてない
	if( network_state == NETWORK_STATE::NONE ){
	  return true;
	}
	//まだつながっていない。
	else if( !has_connection() ){
	  // network_kill_request = true;
	  // network_thread.join();
	  network_thread.detach();
	  // network_kill_request = false;
	  network_state = NETWORK_STATE::NONE;
	  WSACleanup();
	  return true;
	}
	//つながってた
	else{
	  closesocket(sock);
	  WSACleanup();
	  network_kill_request = false;
	  network_state = NETWORK_STATE::NONE;
	  return true;
	}
  }
  
  bool is_network_readable( const SOCKET &socket ){
	fd_set readSet;
	FD_ZERO(&readSet);
	FD_SET(socket, &readSet);
	timeval timeout;
	timeout.tv_sec = 0;  // Zero timeout (poll)
	timeout.tv_usec = 0;
	return (select(socket, &readSet, NULL, NULL, &timeout) == 1);
  }
  std::string read_network(){
	std::string ret;
	if( has_connection() && is_network_readable( (const SOCKET&)sock ) ){
	  memset((void*)network_buffer, 0, sizeof(network_buffer));
	  int n = recv(sock, (char*)network_buffer, sizeof(network_buffer), 0);
	  if (n > 0) {
		ret.assign( (char*)network_buffer );
	  }
	}
	return ret;
  }

  bool write_network( std::string& buffer ){
	if( has_connection() ){
	  int n = send(sock, buffer.c_str(), buffer.size(), 0 );
	  return n > 0;
	}else{
	  return false;
	}
  }

  void server(){
	struct sockaddr_in client;
	int len;
	//SOCKET sock;
	int n;

	//block
	while ( ! network_kill_request ) {
	  len = sizeof(client);
	  sock = accept(sock0, (struct sockaddr *)&client, &len);
	  if (sock == INVALID_SOCKET) {
		printf("accept fail : %d\n", WSAGetLastError());
		return;
	  }else{
		printf("accept ok :\n" );
		network_state = NETWORK_STATE::SERVER_CONNECTED;
		return;
	  }
	}
  }

  bool start_server(){
	WSADATA wsaData;
	struct sockaddr_in addr;

	network_state = NETWORK_STATE::NONE;
	network_kill_request = false;
	
	//start
	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
	  printf("WSAStartup failed\n" );
	  return false;
	}

	//get socket 
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	if (sock0 == INVALID_SOCKET) {
	  printf("socket : %d\n", WSAGetLastError());
	  return false;
	}

	//bind socket
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
	  printf("bind : %d\n", WSAGetLastError());
	  return false;
	}

	//listen 
	if (listen(sock0, 5) != 0) {
	  printf("listen : %d\n", WSAGetLastError());
	  return false;
	}

	network_thread = std::thread( server );
	if( network_thread.joinable() ){
	  set_local_ip();
	  network_state = NETWORK_STATE::SERVER_WAITING;
	  return true;
	}else{
	  WSACleanup();
	  return false;
	}
  }

  bool start_client( std::string ip ){
	WSADATA wsaData;
	struct sockaddr_in server;
	// SOCKET sock;
	network_state = NETWORK_STATE::NONE;
	network_kill_request = false;

	//wsa startup
	if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0) {
	  printf("WSAStartup failed\n");
	  return false;
	}

	//socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
	  printf("socket : %d\n", WSAGetLastError());
	  return false;
	}

	//inet_addrアドレス解決
	server.sin_family = AF_INET;
	server.sin_port = htons(12345);
	server.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	
	//inet_addr失敗
	if (server.sin_addr.S_un.S_addr == 0xffffffff) {
	  struct hostent *host;

	  host = gethostbyname(ip.c_str());
	  if (host == NULL) {
		if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
		  printf("host not found : %s\n", ip.c_str());
		}
		return false;
	  }

	  unsigned int ** addrptr = (unsigned int **)host->h_addr_list;

	  while (*addrptr != NULL) {
		server.sin_addr.S_un.S_addr = *(*addrptr);

		// connect()が成功したらloopを抜けます
		if (connect(sock,
					(struct sockaddr *)&server,
					sizeof(server)) == 0) {
		  break;
		}

		addrptr++;
		// connectが失敗したら次のアドレスで試します
	  }

	  // connectが全て失敗した場合
	  if (*addrptr == NULL) {
		printf("connect : %d\n", WSAGetLastError());
		return false;
	  }
	} else {
	  // inet_addr()が成功したとき
	  // connectが失敗したらエラーを表示して終了
	  if (connect(sock,
				  (struct sockaddr *)&server,
				  sizeof(server)) != 0) {
		printf("connect : %d\n", WSAGetLastError());
		return false;
	  }
	}

	set_local_ip();
	network_state = NETWORK_STATE::CLIENT_CONNECTED;
	return true;
  }

  //---------------------------------------------------------
  //初期化
  //---------------------------------------------------------
  void init( int fps ){
	sys::fps = fps;
	sys::mspf = 1000 / fps;
	sys::last_time = get_time();
	sys::input = -1;
	sys::input_mod = 0;

	//矢印キーとスペースだけ
	last_keys.resize( 4+1 );
	for( int i=0; i<last_keys.size(); ++i ){
	  last_keys[ i ].resize( 2 );
	}

	//乱数初期化
	srand((unsigned int)sys::last_time);
	
	//ニホンゴutf-8
	setlocale(LC_ALL, "");

	//curses 初期化.
	initscr();
	//色を利用。
	start_color();
	//エコーバック無し.
    noecho();
	//returnを待たない.
    cbreak();
	//入力を待たない.
	timeout( 0 );
	//改行をcr, lfに変換しない.
    nonl();
	//F1,F2...を読む。
	keypad(stdscr, TRUE);
	//カーソル表示
    curs_set(1);

	//マウス処理
    mouse_set(ALL_MOUSE_EVENTS);
    PDC_return_key_modifiers(TRUE);
	
    time_t seed;
    seed = time((time_t *)0);
    srand(seed);
  }

  //---------------------------------------------------------
  //終了
  //---------------------------------------------------------
  void exit(){
    curs_set(1);
	endwin();
	kill_connection();
  }

  //---------------------------------------------------------
  //更新
  //---------------------------------------------------------
  void update(){
	wait( mspf );
	request_mouse_pos();
	input = getch();
	input_mod = PDC_get_key_modifiers();

	int keys[] = {VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_SPACE};
	for( int i=0; i<last_keys.size(); ++i ){
	  last_keys[ i ][ 0 ] = last_keys[ i ][ 1 ];
	  last_keys[ i ][ 1 ] = ( 0x8000 & GetAsyncKeyState( keys[i] ) );
	}
  }
  
  //---------------------------------------------------------
  //画面消去
  //---------------------------------------------------------

  void erase_screen(){
	clear();
  }
  
  //---------------------------------------------------------
  //画面描画
  //---------------------------------------------------------
  void draw(){
	refresh();
  }

  //---------------------------------------------------------
  //画面サイズ取得
  //---------------------------------------------------------
  int get_screen_w(){
	int w,h;
	getmaxyx( stdscr, h, w );
	return w;
  }

  int get_screen_h(){
	int w,h;
	getmaxyx( stdscr, h, w );
	return h;
  }

  //---------------------------------------------------------
  //プリント
  //---------------------------------------------------------
  bool is_utf8( std::string &str ){
	long i = 0, j = 0;
	while (str.c_str()[i]){
	  if ((str.c_str()[i] & 0xc0) != 0x80) j++;
	  i++;
	}
	return j != i;
  }
  int strlen_utf8( std::string &str ){
	long i = 0, j = 0;
	while (str.c_str()[i]){
	  if ((str.c_str()[i] & 0xc0) != 0x80) j++;
	  i++;
	}
	return j;
  }

  void print_utf8( int x, int y, std::string &str ){
	long i = 0;
	long j = 0;
	char tmp[ 8 ];

	while (str.c_str()[i]){
	  char c = str.c_str()[i];
	  if( !(c & 0x80) ){
		//ascii
		if( j != 0 ){
		  tmp[ j ] = '\0';
		  move( y, x );
		  printw( tmp );
		  x += 2;
		  j = 0;
		}
		tmp[ 0 ] = c;
		tmp[ 1 ] = '\0';
		move( y, x );
		printw( tmp );
		x += 1;
		j = 0;
	  }else if( (c & 0xC0) == 0xC0 ){
		//utf-8 head
		if( j != 0 ){
		  tmp[ j ] = '\0';
		  move( y, x );
		  printw( tmp );
		  x += 2;
		  j = 0;
		}
		tmp[ j++ ] = c;
	  }else if( (c & 0xC0) == 0x80 ){
		tmp[ j++ ] = c;
		if( i == str.size()-1 ){
		  tmp[ j ] = '\0';
		  move( y, x );
		  printw( tmp );
		  x += 2;
		  j = 0;
		}
	  }
	  i++;
	}
  }
  
  void print( int x, int y, std::string &str ){
	if( is_utf8( str ) ){
	  print_utf8( x, y, str );
	}else{
	  move( y, x );
	  printw( str.c_str() );
	}
  }

  void print( int x, int y, const char *sptr ){
	std::string text = sptr;
	print( x, y, text );
  }

  void print( int x, int y, string_buffer &strb ){
	set_style( strb.fore_color, strb.back_color, strb.style );
	std::string s;
	while( std::getline(strb, s ) ){
	  print( x,y++, s );
	}
	reset_style();
  }

  void print( int x, int y, char c ){
	char str[] = {c,'\0'};
	move( y, x );
	printw( str );
  }
  
  //---------------------------------------------------------
  //文字属性
  //---------------------------------------------------------
  int last_style = 0;
  int last_no = 0;
  int attr_num = 0;
  std::map< int, int > attrs;
  void set_style( int fore_color, int back_color, int style ){
	int a = fore_color | back_color << 16;
	if( attrs.find( a ) == attrs.end() ){
	  attrs.insert( std::make_pair( a, 1 + attrs.size() ) );
	  init_pair( attrs[ a ], fore_color, back_color);
	}
	attron( COLOR_PAIR( attrs[ a ] ) | style );
	last_style = style;
	last_no = attrs[ a ];
  }
  void reset_style(){
	attroff( COLOR_PAIR(last_no) | last_style );
  }

	
  //---------------------------------------------------------
  //カーソル表示、非表示
  //---------------------------------------------------------
  void display_cursor( bool flg ){
	curs_set( (int)flg );
  }
  
  //---------------------------------------------------------
  //マウス関数
  //---------------------------------------------------------
  int get_mouse_x(){
	return MOUSE_X_POS;
  }

  int get_mouse_y(){
	return MOUSE_Y_POS;
  }

  bool is_mouse_pressed( int no ){
	if( no < 0 ){
	  if( is_mouse_pressed( 1 ) ||
		  is_mouse_pressed( 2 ) ||
		  is_mouse_pressed( 3 ) )
		return true;
	  else
		return false;
	}else{
	  int flg =  (BUTTON_STATUS(no) & BUTTON_ACTION_MASK);
	  return ( flg == BUTTON_PRESSED || flg == BUTTON_CLICKED);
	}
  }
  
  int get_mouse_pressed(){
	for( int i=0; i<3; ++i ){
	  if( is_mouse_pressed( i+1 ) ) return i;
	}
	return -1;
  }
  bool get_mouse_l(){
	return is_mouse_pressed(1);
  }
  bool get_mouse_m(){
	return is_mouse_pressed(2);
  }
  bool get_mouse_r(){
	return is_mouse_pressed(3);
  }

  //---------------------------------------------------------
  //エフェクト
  //---------------------------------------------------------
  void play_beep(){
	beep();
  }

  //画面フラッシュ
  void flash_screen(){
	flash();
  }

  
  //---------------------------------------------------------
  //キーボード
  //---------------------------------------------------------
  bool is_key_trigger( int no ){
	return !last_keys[ no ][ 0 ] && last_keys[ no ][ 1 ];
  }
  bool is_key_release( int no ){
	return last_keys[ no ][ 0 ] && !last_keys[ no ][ 1 ];
  }
  bool is_key_press( int no ){
	return last_keys[ no ][ 1 ];
  }

  bool is_up_key_trigger(){ return is_key_trigger( 0 ); }
  bool is_up_key_press(){ return is_key_press( 0 ); }
  bool is_up_key_release(){ return is_key_release( 0 ); }
  bool is_down_key_trigger(){ return is_key_trigger( 1 ); }
  bool is_down_key_press(){ return is_key_press( 1 ); }
  bool is_down_key_release(){ return is_key_release( 1 ); }
  bool is_left_key_trigger(){ return is_key_trigger( 2 ); }
  bool is_left_key_press(){ return is_key_press( 2 ); }
  bool is_left_key_release(){ return is_key_release( 2 ); }
  bool is_right_key_trigger(){ return is_key_trigger( 3 ); }
  bool is_right_key_press(){ return is_key_press( 3 ); }
  bool is_right_key_release(){ return is_key_release( 3 ); }
  
  std::string get_key_info( int key){
	std::string info = " ";
	return info = keyname( key );
  }
  
  int get_key(){
	return input;
  }

  bool is_key_pressed(){
	return input != ERR && input >= 0;
  }
  
  bool get_shift_key(){
	int m = get_mouse_pressed();
	if( m < 0 )
	  return PDC_get_key_modifiers() & PDC_KEY_MODIFIER_SHIFT;
	else
	  return (BUTTON_STATUS(m) & BUTTON_SHIFT);
  }
  bool get_ctrl_key(){
	int m = get_mouse_pressed();
	if( m < 0 )
	  return PDC_get_key_modifiers() & PDC_KEY_MODIFIER_CONTROL;
	else
	  return (BUTTON_STATUS(m) & BUTTON_CONTROL);
  }
  bool get_alt_key(){
	int m = get_mouse_pressed();
	if( m < 0 )
	  return PDC_get_key_modifiers() & PDC_KEY_MODIFIER_ALT;
	else
	  return (BUTTON_STATUS(m) & BUTTON_ALT);
  }

  bool is_escape(){
	return input == 0x1b;
  }
}
