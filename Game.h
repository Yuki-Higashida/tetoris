#pragma once

#define easy "Easy"      //難易度名 Easy
#define normal "Normal"  //難易度名 Normal
#define hard "Hard"      //難易度名 Hard
#define Omino_num 1               //Oミノの出現番号
#define Smino_num 2               //Sミノの出現番号
#define Jmino_num 4               //Jミノの出現番号
#define Lmino_num 5               //Lミノの出現番号
#define Tmino_num 7               //Tミノの出現番号
#define Frame_border 3            //ゲーム画面の枠の太さ
#define Frame_leftX 44            //ゲーム画面枠の左端 
#define Frame_width 10            //ゲーム画面の幅
#define Frame_rightX 60           //ゲーム画面の右端
#define Frame_upY 5               //ゲーム画面の上端
#define Frame_height 20           //ゲーム画面の高さ
#define Frame_downY 25            //ゲーム画面の下端
#define Next_frame_leftX 70       //次のミノを表示する箱の左端
#define Next_frame_rightX 76      //次のミノを表示する箱の右端
#define Next_frame_upY 15         //次のミノを表示する箱の上端
#define Next_frame_downY 22       //次のミノを表示する箱の下端
#define Ini_data_X 90          //プレイヤー名、難易度の表示開始X座標
#define Ini_data_Y 5           //プレイヤー名、難易度の表示開始Y座標



//ゲーム進行、結果に必要なデータの格納
struct Game {
	char plar_name[CHARBUFF];    //プレイヤーの名前
	char dif_level[CHARBUFF];    //難易度名
	double fall_speed;              //ミノの落下スピード
	int Imino_num;               //Iミノの出現番号
	int Zmino_num;               //Zミノの出現番号
	int result_row;              //消去した行数
	int Imino_cnt;               //Iミノを操作した数
	int Omino_cnt;               //Oミノを操作した数
	int Smino_cnt;               //Sミノを操作した数
	int Zmino_cnt;               //Zミノを操作した数
	int Jmino_cnt;               //Jミノを操作した数
	int Lmino_cnt;               //Lミノを操作した数
	int Tmino_cnt;               //Tミノを操作した数
};

void setDifficulty(Game *data);    //難易度による設定
void makeFrame(int height, int width);   //ゲーム画面枠の描画
void outputResult(const char* fileName, Game data);  //結果の出力