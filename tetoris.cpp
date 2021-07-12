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

int main()
{
    //変数宣言
    char currentDirectory[CHARBUFF];
    char mino_name[MINO_TYPE][CHARBUFF] = { "Iミノ","Oミノ","Sミノ","Zミノ","Jミノ","Lミノ","Tミノ" };
    Game tetoris;

    //現在のディレクトリを取得する
    getCurrentDirectory(currentDirectory);

    //設定ファイルから値を読み込む
    readChar("tetoris", "playername", "none", tetoris.plar_name, currentDirectory);
    readChar("tetoris", "difficulty_level", "none", tetoris.dif_level, currentDirectory);

    //難易度設定
    setDifficulty(tetoris);






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
void setDifficulty(Game data) {

}

//ファイルの出力
void outputResult(const char* fileName,Game data) {
    FILE* fp;
    errno_t error;
    int i;

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
