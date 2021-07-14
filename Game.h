#pragma once

#define easy "Easy"      //��Փx�� Easy
#define normal "Normal"  //��Փx�� Normal
#define hard "Hard"      //��Փx�� Hard
#define Omino_num 1               //O�~�m�̏o���ԍ�
#define Smino_num 2               //S�~�m�̏o���ԍ�
#define Jmino_num 4               //J�~�m�̏o���ԍ�
#define Lmino_num 5               //L�~�m�̏o���ԍ�
#define Tmino_num 7               //T�~�m�̏o���ԍ�
#define Frame_border 3            //�Q�[����ʂ̘g�̑���
#define Frame_leftX 44            //�Q�[����ʘg�̍��[ 
#define Frame_width 10            //�Q�[����ʂ̕�
#define Frame_rightX 60           //�Q�[����ʂ̉E�[
#define Frame_upY 5               //�Q�[����ʂ̏�[
#define Frame_height 20           //�Q�[����ʂ̍���
#define Frame_downY 25            //�Q�[����ʂ̉��[
#define Next_frame_leftX 70       //���̃~�m��\�����锠�̍��[
#define Next_frame_rightX 76      //���̃~�m��\�����锠�̉E�[
#define Next_frame_upY 15         //���̃~�m��\�����锠�̏�[
#define Next_frame_downY 22       //���̃~�m��\�����锠�̉��[
#define Ini_data_X 90          //�v���C���[���A��Փx�̕\���J�nX���W
#define Ini_data_Y 5           //�v���C���[���A��Փx�̕\���J�nY���W



//�Q�[���i�s�A���ʂɕK�v�ȃf�[�^�̊i�[
struct Game {
	char plar_name[CHARBUFF];    //�v���C���[�̖��O
	char dif_level[CHARBUFF];    //��Փx��
	double fall_speed;              //�~�m�̗����X�s�[�h
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