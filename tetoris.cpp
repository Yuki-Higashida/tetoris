// tetoris.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "Setting.h"
#include "Mino.h"
#include "Game.h"

int x;      //ミノのX座標
int y;      //ミノのY座標

int main()
{
    char currentDirectory[CHARBUFF];
    char mino_name[MINO_TYPE][CHARBUFF] = { "Iミノ","Oミノ","Sミノ","Zミノ","Jミノ","Lミノ","Tミノ" };
    Game tetoris;
    int i, j;

    //現在のディレクトリを取得する
    getCurrentDirectory(currentDirectory);

    //設定ファイルから値を読み込む
    readChar("tetoris", "playername", "none", tetoris.plar_name, currentDirectory);
    readChar("tetoris", "difficulty_level", "none", tetoris.dif_level, currentDirectory);

    //難易度設定
    setDifficulty(&tetoris);

    //描画開始
    //端末の準備
    initscr();

    //画面の幅と高さを取得
    int width, height;
    getmaxyx(stdscr, height, width);

    //色の準備
    start_color();

    //カラーペアの登録
    init_pair(1, COLOR_BLACK, COLOR_CYAN);     //Iミノのカラーペア
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);   //Oミノのカラーペア
    init_pair(3, COLOR_BLACK, COLOR_GREEN);    //Sミノのカラーペア
    init_pair(4, COLOR_BLACK, COLOR_RED);      //Zミノのカラーペア
    init_pair(5, COLOR_BLACK, COLOR_BLUE);     //J,Lミノのカラーペア
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);  //Tミノのカラーペア
    init_pair(7, COLOR_BLACK, COLOR_WHITE);    //ゲーム画面枠、文字の色
    init_pair(8, COLOR_BLACK, COLOR_BLACK);    //背景色
    bkgd(COLOR_PAIR(8));

    //キー操作の取得
    int key;

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    //ゲーム画面枠の描画
    attrset(COLOR_PAIR(7));
    makeFrame(height, width);
    

    //プレイヤー名、難易度を描画
    attrset(COLOR_PAIR(7) | A_REVERSE);
    mvaddstr(Ini_data_Y, Ini_data_X-13, "Player Name: ");
    mvaddstr(Ini_data_Y, Ini_data_X, tetoris.plar_name);
    mvaddstr(Ini_data_Y+1, Ini_data_X-18, "Difficulty Level: ");
    mvaddstr(Ini_data_Y+1, Ini_data_X, tetoris.dif_level);
    


    

    while (1) {
        key = getch();
        if (key == 'q') {
            break;
        }
        
    }
    



    //端末制御の終了
    endwin();

    //ファイル出力
    outputResult("output.txt", tetoris);

    return 0;
}

//ファイルのディレクトリ取得
void getCurrentDirectory(char* currentDirectory) {
    GetCurrentDirectory(CHARBUFF, currentDirectory);
}

//文字列の読み込み
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath) {
    char section_name[CHARBUFF];
    sprintf_s(section_name, section);
    char key[CHARBUFF];
    sprintf_s(key, keyword);
    char settingFile[CHARBUFF];
    sprintf_s(settingFile, "%s\\setting.ini", filePath);

    if (GetPrivateProfileString(section_name, key, defaultValue, returnValue, CHARBUFF, settingFile) == 0) {
        fprintf(stdout, "%s doesn't contain [%s] %s\n", settingFile, section, key);
    }

    return 0;
}

//難易度による設定
void setDifficulty(Game *data) {
    //easyでは1.5秒に1マス落ちる
    if (strcmp(data->dif_level, easy) == 0) {
        data->fall_speed = 1.5;
        data->Zmino_num = 8;
    }
    //normalでは1秒に1マス落ちる
    else if (strcmp(data->dif_level, normal) == 0) {
        data->fall_speed = 1;
        data->Imino_num = 0;
        data->Zmino_num = 9;
    }
    //hardでは0.5秒に1マス落ちる
    else if (strcmp(data->dif_level, hard) == 0) {
        data->fall_speed = 0.5;
        data->Imino_num = 8;
    }
    
}

//ゲーム画面枠の描画
void makeFrame(int height, int width) {
    int i, j;
    //ゲーム画面枠、次のミノを表示する箱の描画
    for (i = 0;i < width;i++) {
        for (j = 0;j < height;j++) {
            if (i == Frame_leftX) {
                mvaddstr(j, i, "   ");
            }
            else if (i == Frame_rightX - Frame_border) {
                mvaddstr(j, i, "   ");
            }
            else if ((j < Frame_upY) && (Frame_leftX <= i) && (i < Frame_rightX)) {
                mvaddstr(j, i, " ");
            }
            else if ((Frame_downY <= j) && (Frame_leftX <= i) && (i < Frame_rightX)) {
                mvaddstr(j, i, " ");
            }
            else if ((i == Next_frame_leftX) && (Next_frame_upY <= j) && (j <= Next_frame_downY)) {
                mvaddstr(j, i, " ");
            }
            else if ((i == Next_frame_rightX) && (Next_frame_upY <= j) && (j <= Next_frame_downY)) {
                mvaddstr(j, i, " ");
            }
            else if ((j == Next_frame_upY) && (Next_frame_leftX <= i) && (i <= Next_frame_rightX)) {
                mvaddstr(j, i, " ");
            }
            else if ((j == Next_frame_downY) && (Next_frame_leftX <= i) && (i <= Next_frame_rightX)) {
                mvaddstr(j, i, " ");
            }
        }
    }
}

//ファイルの出力
void outputResult(const char* fileName,Game data) {
    FILE* fp;
    errno_t error;

    error = fopen_s(&fp, fileName, "w");
    if (error != 0) {
        fprintf_s(stderr, "failed to open");
    }
    else {
        fprintf_s(fp, "あなたが消去した行数は、%d行です。\n", data.result_row);
        fprintf_s(fp, "プレイしたミノの数:\n");
        fprintf_s(fp, "Iミノ:%d個\n", data.Imino_cnt);
        fprintf_s(fp, "Oミノ:%d個\n", data.Omino_cnt);
        fprintf_s(fp, "Sミノ:%d個\n", data.Smino_cnt);
        fprintf_s(fp, "Zミノ:%d個\n", data.Zmino_cnt);
        fprintf_s(fp, "Jミノ:%d個\n", data.Jmino_cnt);
        fprintf_s(fp, "Lミノ:%d個\n", data.Lmino_cnt);
        fprintf_s(fp, "Tミノ:%d個\n", data.Tmino_cnt);

        fclose(fp);
    }
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
