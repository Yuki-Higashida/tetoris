#pragma once

//��Փx
#define EASY "Easy"      //��Փx�� Easy
#define NORMAL "Normal"  //��Փx�� Normal
#define HARD "Hard"      //��Փx�� Hard

//�e�~�m�̏o���ԍ�
#define OMINO_NUM 1               //O�~�m�̏o���ԍ�
#define SMINO_NUM 2               //S�~�m�̏o���ԍ�
#define JMINO_NUM 4               //J�~�m�̏o���ԍ�
#define LMINO_NUM 5               //L�~�m�̏o���ԍ�
#define TMINO_NUM 7               //T�~�m�̏o���ԍ�

//�Q�[����ʘg�̒[���W
#define FRAME_BORDER 3            //�Q�[����ʂ̘g�̑���
#define FRAME_WIDTH 10            //�Q�[����ʂ̕�
#define FRAME_LEFT_X 44           //�Q�[����ʘg�̍��[ 
#define FRAME_RIGHT_X 70          //�Q�[����ʂ̉E�[
#define FRAME_HEIGHT 20           //�Q�[����ʂ̍���
#define FRAME_UP_Y 5              //�Q�[����ʂ̏�[
#define FRAME_DOWN_Y 25           //�Q�[����ʂ̉��[

//���̃~�m��\������g�̒[���W
#define NEXT_BOX_LEFT_X 70        //���̃~�m��\�����锠�̍��[
#define NEXT_BOX_RIGHT_X 81       //���̃~�m��\�����锠�̉E�[
#define NEXT_BOX_UP_Y 13          //���̃~�m��\�����锠�̏�[
#define NEXT_BOX_DOWN_Y 22        //���̃~�m��\�����锠�̉��[

//ini�t�@�C���̓��e��\��������W
#define INI_DATA_X 95             //�v���C���[���A��Փx�̕\���J�nX���W
#define INI_DATA_Y 5              //�v���C���[���A��Փx�̕\���J�nY���W

//�~�m�𐶐�����J�n���W
#define START_X 55                //�~�m�𐶐�����X���W
#define START_Y 5                 //�~�m�𐶐�����Y���W

//���삷��~�m�ɑ΂��鑀�삩���̃~�m�ɑ΂��鑀�삩
#define TO_OPERATE_MINO 0         //���삷��~�m
#define TO_NEXT_MINO 1            //���̃~�m

//����ɂ����铮��
#define LEFT_MOVE 0               //���ւ̈ړ�
#define RIGHT_MOVE 1              //�E�ւ̈ړ�
#define DOWN_MOVE 2               //���ւ̈ړ�
#define AUTO_DOWN_MOVE 3          //���R�����̈ړ�
#define ROLL_MOVE 4               //��]


//�Q�[���i�s�A���ʂɕK�v�ȃf�[�^�̊i�[
struct Game {
	char plar_name[CHARBUFF];    //�v���C���[�̖��O
	char dif_level[CHARBUFF];    //��Փx��
	double fall_speed;           //�~�m�̗����X�s�[�h
	int Imino_num;               //I�~�m�̏o���ԍ�
	int Zmino_num;               //Z�~�m�̏o���ԍ�
	int result_row;              //���������s��
	int Imino_cnt;               //I�~�m�𑀍삵����
	int Omino_cnt;               //O�~�m�𑀍삵����
	int Smino_cnt;               //S�~�m�𑀍삵����
	int Zmino_cnt;               //Z�~�m�𑀍삵����
	int Jmino_cnt;               //J�~�m�𑀍삵����
	int Lmino_cnt;               //L�~�m�𑀍삵����
	int Tmino_cnt;               //T�~�m�𑀍삵����
};

void setDifficulty(Game *data);    //��Փx�ɂ��ݒ�
void makeFrame(int height, int width);   //�Q�[����ʘg�̕`��
void outputResult(const char* fileName, Game data);  //���ʂ̏o��