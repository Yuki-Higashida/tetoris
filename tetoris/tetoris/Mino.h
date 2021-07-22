#pragma once


#define MINO_TYPE 7                      //ミノの種類数
#define MINO_BLOCK 4                     //1つのミノを構成するブロック数
#define MINO_WIDTH 4                     //ミノの幅
#define MINO_HEIGHT 4                    //ミノの高さ
#define MINO_NUM MINO_WIDTH*MINO_HEIGHT  //ブロックのマス数

struct Mino
{
	int color_num;    //ミノの色番号
	int shape[4][4];  //ミノの形
};

void drawBlock(int y, int x);                                                                 //ブロックの描画
void drawMino(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int color, int to_mino);       //ミノの描画
void deleteMino(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int to_mino);                //ミノを画面から消去
int isMoveable(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int move);                    //移動先の座標にミノが動けるか接地判定
int isCreatable(int mino[MINO_HEIGHT][MINO_WIDTH]);                                           //新たなミノを作れるか終了判定
void makeMino(Game data);                                                                     //ランダムにミノを作成
void updateOperateMino();                                                                     //次のミノから操作するミノを取り出して更新
void moveMino(int mino[MINO_HEIGHT][MINO_WIDTH], int move);                                   //ミノの移動
void rollMino(int y,int x, int mino[MINO_HEIGHT][MINO_WIDTH]);                                //ミノの回転 
int isDeletable();                                                                            //削除する行があるか判定
int deleteRow(Game *data);                                                                    //埋まった行の削除
void slideRow(int row_num);                                                                   //行を削除した後全体を1行下げる
void fallMino();                                                                     //ミノを自由落下させる
