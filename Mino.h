#pragma once


#define MINO_TYPE 7                      //�~�m�̎�ސ�
#define MINO_BLOCK 4                     //1�̃~�m���\������u���b�N��
#define MINO_WIDTH 4                     //�~�m�̕�
#define MINO_HEIGHT 4                    //�~�m�̍���
#define MINO_NUM MINO_WIDTH*MINO_HEIGHT  //�u���b�N�̃}�X��

struct Mino
{
	int color_num;    //�~�m�̐F�ԍ�
	int shape[4][4];  //�~�m�̌`
};

void drawBlock(int y, int x);               //�u���b�N�̕`��
void drawMino(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int color, int to_mino);       //�~�m�̕`��
void deleteMino(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int to_mino);                //�~�m����ʂ������
int isMoveable(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int move);                    //�ړ���̍��W�Ƀ~�m�������邩�ڒn����
void makeMino(Game data);                                                                     //�����_���Ƀ~�m���쐬
void updateOperateMino();                                                                     //���̃~�m���瑀�삷��~�m�����o���čX�V
void moveMino(int mino[MINO_HEIGHT][MINO_WIDTH], int move);                                   //�~�m�̈ړ�
void rollMino(int mino[MINO_HEIGHT][MINO_WIDTH]);                                             //�~�m�̉�] 
