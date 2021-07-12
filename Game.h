#pragma once

#define Test 0

//ゲーム進行、結果に必要なデータの格納
struct Game {
	char plar_name[CHARBUFF];    //プレイヤーの名前
	char dif_level[CHARBUFF];    //難易度名
	int fall_speed;              //ミノの落下スピード
	int Imino_rate;              //Iミノの出現確率
	int SZmino_rate;             //SミノとZミノの出現確率
	int result_row;              //消去した行数
	int Imino_cnt;               //Iミノを操作した数
	int Omino_cnt;               //Oミノを操作した数
	int Smino_cnt;               //Sミノを操作した数
	int Zmino_cnt;               //Zミノを操作した数
	int Jmino_cnt;               //Jミノを操作した数
	int Lmino_cnt;               //Lミノを操作した数
	int Tmino_cnt;               //Tミノを操作した数
};

void setDifficulty(Game data);    //難易度による設定
void makeGameFrame(Game data);            //ゲーム画面の枠を描画
void outputResult(const char* fileName, int result, Game data);  //結果の出力