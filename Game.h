#pragma once

#define Test 0

//�Q�[���i�s�A���ʂɕK�v�ȃf�[�^�̊i�[
struct Game {
	char plar_name[CHARBUFF];    //�v���C���[�̖��O
	char dif_level[CHARBUFF];    //��Փx��
	int fall_speed;              //�~�m�̗����X�s�[�h
	int Imino_rate;              //I�~�m�̏o���m��
	int SZmino_rate;             //S�~�m��Z�~�m�̏o���m��
	int result_row;              //���������s��
	int Imino_cnt;               //I�~�m�𑀍삵����
	int Omino_cnt;               //O�~�m�𑀍삵����
	int Smino_cnt;               //S�~�m�𑀍삵����
	int Zmino_cnt;               //Z�~�m�𑀍삵����
	int Jmino_cnt;               //J�~�m�𑀍삵����
	int Lmino_cnt;               //L�~�m�𑀍삵����
	int Tmino_cnt;               //T�~�m�𑀍삵����
};

void setDifficulty(Game data);    //��Փx�ɂ��ݒ�
void makeGameFrame(Game data);            //�Q�[����ʂ̘g��`��
void outputResult(const char* fileName, int result, Game data);  //���ʂ̏o��