// tetoris.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "Setting.h"
#include "Game.h"
#include "Mino.h"

int pos_x = START_X;          //ミノのX座標
int pos_y = START_Y;         //ミノのY座標
int stopFlag = 0;    //ミノの静止フラグ
int exitFlag = 0;
int key;             //取得したキーの格納
int ope_color;           //操作するミノの色
int next_color;          //次のミノの色
int game_field[FRAME_HEIGHT][FRAME_WIDTH];    //ゲームフィールド
int operate_mino[MINO_HEIGHT][MINO_WIDTH];    //操作するミノ
int next_mino[MINO_HEIGHT][MINO_WIDTH];       //次のミノ

struct Mino minos[MINO_TYPE] = {
    //Iミノ
    {
        {1},
        {{0,1,0,0},
         {0,1,0,0},
         {0,1,0,0},
         {0,1,0,0}}
    },
    //Oミノ
    {
        {2},
        {{0,0,0,0},
         {0,2,2,0},
         {0,2,2,0},
         {0,0,0,0}}
    },
    //Sミノ
    {
        {3},
        {{0,0,0,0},
         {0,3,3,0},
         {3,3,0,0},
         {0,0,0,0}}
    },
    //Zミノ
    {
        {4},
        {{0,0,0,0},
         {4,4,0,0},
         {0,4,4,0},
         {0,0,0,0}}
    },
    //Jミノ
    {
        {5},
        {{0,0,0,0},
         {5,0,0,0},
         {5,5,5,0},
         {0,0,0,0}}
    },
    //Lミノ
    {
        {5},
        {{0,0,0,0},
         {0,0,5,0},
         {5,5,5,0},
         {0,0,0,0}}
    },
    //Tミノ
    {
        {6},
        {{0,0,0,0},
         {0,6,0,0},
         {6,6,6,0},
         {0,0,0,0}}
    }
};

void debug();
void debug1();

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
    init_pair(8, COLOR_BLACK, COLOR_BLACK);    //背景色、塗りつぶし色
    bkgd(COLOR_PAIR(8));

    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    attrset(COLOR_PAIR(7));
    //ゲーム開始前の待機画面
    mvaddstr(15, 52, "Push Space button!");
    while (1) {
        key = getch();
        if (key == ' ') {
            break;
        }

    }
    erase();

    //ゲーム画面枠の描画
    makeFrame(height, width);
    

    //プレイヤー名、難易度、説明を描画
    attrset(COLOR_PAIR(7) | A_REVERSE);
    mvaddstr(INI_DATA_Y, INI_DATA_X-13, "Player Name: ");
    mvaddstr(INI_DATA_Y, INI_DATA_X, tetoris.plar_name);
    mvaddstr(INI_DATA_Y+1, INI_DATA_X-18, "Difficulty Level: ");
    mvaddstr(INI_DATA_Y+1, INI_DATA_X, tetoris.dif_level);
    mvaddstr(NEXT_BOX_UP_Y + 1, INI_DATA_X - 5, "move : ← ↓ → ");
    mvaddstr(NEXT_BOX_UP_Y + 2, INI_DATA_X - 5, "roll : Space");
    mvaddstr(NEXT_BOX_DOWN_Y + 2, INI_DATA_X - 5, "Press the Q button");
    mvaddstr(NEXT_BOX_DOWN_Y + 3, INI_DATA_X - 12, "when you want to quit this game");
    
    //最初のミノを次に落下するミノに追加
    makeMino(tetoris);
    Sleep(1000);

    //ゲーム開始
    while (1) {
        //次に落下するミノからミノを取り出し開始位置に描画
        updateOperateMino();
        drawMino(pos_y, pos_x, operate_mino, ope_color, TO_OPERATE_MINO);

        //次に落下するミノに表示していたミノを消す
        deleteMino(NEXT_BOX_UP_Y + 2, NEXT_BOX_LEFT_X + 2,next_mino,TO_NEXT_MINO);

        //ランダムにミノを生成し次に落下するミノに追加
        makeMino(tetoris);
        drawMino(NEXT_BOX_UP_Y + 2, NEXT_BOX_LEFT_X + 2, next_mino, next_color, TO_NEXT_MINO);
;
        //ミノの操作
        //接地判定により操作終了
        while (isMoveable(pos_y, pos_x, operate_mino, DOWN_MOVE)) {
            if (exitFlag) {
                break;
            }
            
            key = getch();

            switch (key)
            {
            case KEY_LEFT:
                if (isMoveable(pos_y, pos_x, operate_mino, LEFT_MOVE)) {
                    moveMino(operate_mino, LEFT_MOVE);
                }
                break;
            case KEY_RIGHT:
                if (isMoveable(pos_y, pos_x, operate_mino, RIGHT_MOVE)) {
                    moveMino(operate_mino, RIGHT_MOVE);
                }
                break;
            case KEY_DOWN:
                if (isMoveable(pos_y, pos_x, operate_mino, DOWN_MOVE)) {
                    moveMino(operate_mino, DOWN_MOVE);
                    debug();
                }
                break;
            case ' ':
                if (isMoveable(pos_y, pos_x, operate_mino, ROLL_MOVE)) {
                    rollMino(operate_mino);
                }
                break;
            case 'q':
                exitFlag = 1;
                break;
            default:
                break;
            }
            
        }
        if (exitFlag) {
            break;
        }

        fprintf_s(stdout, "yo");
        

        //値の初期化
        pos_x = START_X;
        pos_y = START_Y;
        
    }
    



    //端末制御の終了
    endwin();

    //ファイル出力
    outputResult("output.txt", tetoris);

    return 0;
}

void debug() {
    int i, j;
    for (i = 0;i < FRAME_HEIGHT;i++) {
        for (j = 0;j < FRAME_WIDTH;j++) {
            fprintf_s(stdout, "%d,", game_field[i][j]);
        }
        fprintf_s(stdout, "\n");
    }
}

void debug1() {
    int i, j;
    for (i = 0;i < MINO_HEIGHT;i++) {
        for (j = 0;j < MINO_WIDTH;j++) {
            fprintf_s(stdout, "%d,", next_mino[i][j]);
        }
        fprintf_s(stdout, "\n");
    }
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
    if (strcmp(data->dif_level, EASY) == 0) {
        data->fall_speed = 1.5;
        data->Zmino_num = 8;
    }
    //normalでは1秒に1マス落ちる
    else if (strcmp(data->dif_level, NORMAL) == 0) {
        data->fall_speed = 1;
        data->Imino_num = 0;
        data->Zmino_num = 9;
    }
//hardでは0.5秒に1マス落ちる
    else if (strcmp(data->dif_level, HARD) == 0) {
    data->fall_speed = 0.5;
    data->Imino_num = 8;
    }

}

//ゲーム画面枠の描画
void makeFrame(int height, int width) {
    int i, j;
    attrset(COLOR_PAIR(7));
    //ゲーム画面枠、次のミノを表示する箱の描画
    for (i = 0;i < height;i++) {
        for (j = 0;j < width;j++) {
            if (j == FRAME_LEFT_X) {
                mvaddstr(i, j, "   ");
            }
            else if (j == FRAME_RIGHT_X - FRAME_BORDER) {
                mvaddstr(i, j, "   ");
            }
            else if ((i < FRAME_UP_Y) && (FRAME_LEFT_X <= j) && (j < FRAME_RIGHT_X)) {
                mvaddstr(i, j, " ");
            }
            else if ((FRAME_DOWN_Y <= i) && (FRAME_LEFT_X <= j) && (j < FRAME_RIGHT_X)) {
                mvaddstr(i, j, " ");
            }
            else if ((j == NEXT_BOX_LEFT_X) && (NEXT_BOX_UP_Y <= i) && (i <= NEXT_BOX_DOWN_Y)) {
                mvaddstr(i, j, " ");
            }
            else if ((j == NEXT_BOX_RIGHT_X) && (NEXT_BOX_UP_Y <= i) && (i <= NEXT_BOX_DOWN_Y)) {
                mvaddstr(i, j, " ");
            }
            else if ((i == NEXT_BOX_UP_Y) && (NEXT_BOX_LEFT_X <= j) && (j <= NEXT_BOX_RIGHT_X)) {
                mvaddstr(i, j, " ");
            }
            else if ((i == NEXT_BOX_DOWN_Y) && (NEXT_BOX_LEFT_X <= j) && (j <= NEXT_BOX_RIGHT_X)) {
                mvaddstr(i, j, " ");
            }
        }
    }
}

//移動先の座標にミノが動けるか接地判定
int isMoveable(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int move) {
    int i, j;
    int result = 1;
    int g_y, g_x;
    int has_block_row, has_block_line;

    switch (move)
    {
    case LEFT_MOVE:
        for (i = 0;i < MINO_WIDTH;i++) {
            for (j = 0;j < MINO_HEIGHT;j++) {
                if (mino[j][i] != 0) {
                    has_block_row = i;
                    i = MINO_WIDTH;
                }
            }
        }
        g_x = has_block_row + (x - FRAME_BORDER - FRAME_LEFT_X) / 2;
        for (i = 0;i < MINO_HEIGHT;i++) {
            g_y = i + y - FRAME_UP_Y;
            if (mino[i][has_block_row] != 0) {
                if (g_x == 0) {
                    result = 0;
                }
                else {
                    if (game_field[g_y][g_x - 1] != 0) {
                        result = 0;
                    }
                }
            }
        }
        break;
    case RIGHT_MOVE:
        for (i = 0;i < MINO_WIDTH;i++) {
            for (j = 0;j < MINO_HEIGHT;j++) {
                if (mino[j][i] != 0) {
                    has_block_row = i;
                }
            }
        }
        g_x = has_block_row + (x - FRAME_BORDER - FRAME_LEFT_X) / 2;
        for (i = 0;i < MINO_HEIGHT;i++) {
            g_y = i + y - FRAME_UP_Y;
            if (mino[i][has_block_row] != 0) {
                if (g_x == FRAME_WIDTH - 1) {
                    result = 0;
                }
                else {
                    if (game_field[g_y][g_x + 1] != 0) {
                        result = 0;
                    }
                }
            }
        }
        break;
    case DOWN_MOVE:
    case AUTO_DOWN_MOVE:
        for (i = 0;i < MINO_HEIGHT;i++) {
            g_y = i + y - FRAME_UP_Y;
            for (j = 0;j < MINO_WIDTH;j++) {
                g_x = j + (x - FRAME_BORDER - FRAME_LEFT_X) / 2;
                if (mino[i][j] != 0) {
                    if (g_y == FRAME_HEIGHT - 1) {
                        result = 0;
                    }
                    else {
                        if (i < MINO_HEIGHT - 1) {
                            if (mino[i + 1][j] == 0) {
                                if (game_field[g_y + 1][g_x] != 0) {
                                    result = 0;
                                }
                            }
                        }
                        else {
                            if (game_field[g_y + 1][g_x] != 0) {
                                result = 0;
                            }
                        }
                        
                    }
                }
            }
        }
        break;
    case ROLL_MOVE:

        break;
    default:
        break;
    }
    return result;
}

//ブロックの描画
void drawBlock(int y, int x) {
    mvaddstr(y, x, "□");
}

//ミノの描画
void drawMino(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int color, int to_mino) {
    int i, j;
    int g_y, g_x;

    attrset(COLOR_PAIR(color));
    for (i = 0;i < MINO_HEIGHT;i++) {
        g_y = i + y - FRAME_UP_Y;
        for (j = 0;j < MINO_WIDTH;j++) {
            g_x = j + (x - FRAME_BORDER - FRAME_LEFT_X) / 2;
            if (mino[i][j] > 0) {
                drawBlock(i + y, j * 2 + x);
                if (to_mino == TO_OPERATE_MINO) {
                    game_field[g_y][g_x] = mino[i][j];
                }
            }
        }
    }
}

//ミノを画面から消去
void deleteMino(int y, int x, int mino[MINO_HEIGHT][MINO_WIDTH], int to_mino) {
    int i, j;
    int g_y, g_x;

    attrset(COLOR_PAIR(8));
    for (i = 0;i < MINO_HEIGHT;i++) {
        g_y = i + y - FRAME_UP_Y;
        for (j = 0;j < MINO_WIDTH;j++) {
            g_x = j + (x - FRAME_BORDER - FRAME_LEFT_X) / 2;
            if (mino[i][j] > 0) {
                drawBlock(i + y, j * 2 + x);
                if (to_mino == TO_OPERATE_MINO) {
                    game_field[g_y][g_x] = 0;
                }
            }
        }
    }
}

//ランダムにミノを作成
void makeMino(Game data) {
    //0~9でランダムに整数値を取得
    srand((unsigned int)time(NULL));
    int randMino;
    int mino_num = 0;
    int color_num = 0;
    int i, j;

    for (i = 0;i < 10;i++) {
        randMino = rand() % 10;
    }

    switch (randMino)
    {
    case OMINO_NUM:
        mino_num = 1;
        break;
    case SMINO_NUM:
        mino_num = 2;
        break;
    case JMINO_NUM:
        mino_num = 4;
        break;
    case LMINO_NUM:
        mino_num = 5;
        break;
    case TMINO_NUM:
        mino_num = 6;
    default:
        break;
    }

    if (strcmp(data.dif_level, EASY) == 0) {
        switch (randMino)
        {
        case 0:
        case 3:
        case 6:
        case 9:
            mino_num = 0;
            break;
        case 8:
            mino_num = 3;
        default:
            break;
        }
    }
    else if (strcmp(data.dif_level, NORMAL) == 0) {
        switch (randMino)
        {
        case 0:
        case 6:
        case 9:
            mino_num = 0;
            break;
        case 3:
        case 8:
            mino_num = 3;
        default:
            break;
        }
    }
    else if (strcmp(data.dif_level, HARD) == 0) {
        switch (randMino)
        {
        case 0:
        case 3:
        case 6:
        case 9:
            mino_num = 3;
            break;
        case 8:
            mino_num = 0;
        default:
            break;
        }
    }

    //次のミノにミノの形情報を代入
    for (i = 0;i < MINO_HEIGHT;i++) {
        for (j = 0;j < MINO_WIDTH;j++) {
            next_mino[i][j] = minos[mino_num].shape[i][j];
        }
    }
    next_color = minos[mino_num].color_num;
}

//次のミノから操作するミノを取り出して更新
void updateOperateMino() {
    int i, j;

    ope_color = next_color;

    for (i = 0;i < MINO_HEIGHT;i++) {
        for (j = 0;j < MINO_WIDTH;j++) {
            operate_mino[i][j] = next_mino[i][j];
        }
    }
}

//ミノの移動
void moveMino(int mino[MINO_HEIGHT][MINO_WIDTH], int move) {
    switch (move)
    {
    case LEFT_MOVE:
        deleteMino(pos_y, pos_x, operate_mino, TO_OPERATE_MINO);
        pos_x = pos_x - 2;
        drawMino(pos_y, pos_x, operate_mino, ope_color, TO_OPERATE_MINO);
        break;
    case RIGHT_MOVE:
        deleteMino(pos_y, pos_x, operate_mino, TO_OPERATE_MINO);
        pos_x = pos_x + 2;
        drawMino(pos_y, pos_x, operate_mino, ope_color, TO_OPERATE_MINO);
        break;
    case DOWN_MOVE:
        deleteMino(pos_y, pos_x, operate_mino, TO_OPERATE_MINO);
        pos_y++;
        drawMino(pos_y, pos_x, operate_mino, ope_color, TO_OPERATE_MINO);
        break;
    case AUTO_DOWN_MOVE:
        deleteMino(pos_y, pos_x, operate_mino, TO_OPERATE_MINO);
        pos_y++;
        drawMino(pos_y, pos_x, operate_mino, ope_color, TO_OPERATE_MINO);
        break;
    default:
        break;
    }
}

//ミノの回転
void rollMino(int mino[MINO_HEIGHT][MINO_WIDTH]) {

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
