#pragma once

//難易度
#define EASY "Easy"      //難易度名 Easy
#define NORMAL "Normal"  //難易度名 Normal
#define HARD "Hard"      //難易度名 Hard

//各ミノの出現番号
#define OMINO_NUM 1               //Oミノの出現番号
#define SMINO_NUM 2               //Sミノの出現番号
#define JMINO_NUM 4               //Jミノの出現番号
#define LMINO_NUM 5               //Lミノの出現番号
#define TMINO_NUM 7               //Tミノの出現番号

//ゲーム画面枠の端座標
#define FRAME_BORDER 3            //ゲーム画面の枠の太さ
#define FRAME_WIDTH 10            //ゲーム画面の幅
#define FRAME_LEFT_X 44           //ゲーム画面枠の左端 
#define FRAME_RIGHT_X 70          //ゲーム画面の右端
#define FRAME_HEIGHT 20           //ゲーム画面の高さ
#define FRAME_UP_Y 5              //ゲーム画面の上端
#define FRAME_DOWN_Y 25           //ゲーム画面の下端

//次のミノを表示する枠の端座標
#define NEXT_BOX_LEFT_X 70        //次のミノを表示する箱の左端
#define NEXT_BOX_RIGHT_X 81       //次のミノを表示する箱の右端
#define NEXT_BOX_UP_Y 13          //次のミノを表示する箱の上端
#define NEXT_BOX_DOWN_Y 22        //次のミノを表示する箱の下端

//iniファイルの内容を表示する座標
#define INI_DATA_X 95             //プレイヤー名、難易度の表示開始X座標
#define INI_DATA_Y 5              //プレイヤー名、難易度の表示開始Y座標

//ミノを生成する開始座標
#define START_X 55                //ミノを生成するX座標
#define START_Y 5                 //ミノを生成するY座標

//操作するミノに対する操作か次のミノに対する操作か
#define TO_OPERATE_MINO 0         //操作するミノ
#define TO_NEXT_MINO 1            //次のミノ

//操作における動き
#define LEFT_MOVE 0               //左への移動
#define RIGHT_MOVE 1              //右への移動
#define DOWN_MOVE 2               //下への移動
#define AUTO_DOWN_MOVE 3          //自由落下の移動
#define ROLL_MOVE 4               //回転


//ゲーム進行、結果に必要なデータの格納
struct Game {
	char plar_name[CHARBUFF];    //プレイヤーの名前
	char dif_level[CHARBUFF];    //難易度名
	double fall_speed;           //ミノの落下スピード
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