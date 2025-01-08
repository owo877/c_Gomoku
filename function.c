#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// 8方向量
Position vL[8] = {
    {-1, -1},
    { 0, -1},
    { 1, -1},
    {-1,  0},
    { 1,  0},
    {-1,  1},
    { 0,  1},
    { 1,  1}
};
int colorSame(char pieces, char color){
    return color == pieces;
}
// 回傳下棋座標
void returnAns(Position pos){
    printf("%c, %d", pos.y+'A', pos.x);
}
// 控制是否顯示
void print(char *str){
    if(printControl)printf("%s", str);
}
// show chess
void showChess(Position pos, Pieces target){
    printf("\x1b[91m");
    printf("x: %02d y: %02d | color: %d\n", pos.x+1, pos.y+1, target.color);
    printf("\x1b[0m");

    printf("\x1b[96m");
    printf("連幾顆: %d | 跳第: %d | 方向: %d\n", target.link, target.jump, target.v);
    printf("\x1b[0m");
}
// 顯示當前棋盤
void show(){
    int i, j;
    // printf("\n   A B C D E F G H I J K L M N O P Q R S | Y\n");
    printf("\n   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 Y\n");
    for (i=0; i<BoardSize; i++){
        printf("%2d ", i+1);
        for(j=0; j<BoardSize; j++){
            if(chessBoard[i][j] == '0'){
                printf("\x1b[47m\x1b[30m");
            }
            else if(chessBoard[i][j] == '1'){
                printf("\x1b[40m");
            }
            else if(chessBoard[i][j] == '2'){
                printf("\x1b[44m");
            }
            else if(chessBoard[i][j] == '3'){
                printf("\x1b[41m");
            }
            printf("%c", chessBoard[i][j]);
            printf("\x1b[0m ");
        }
        printf("\n");
    }
    printf(" X\n");
}

// 判斷連線數 
// -answer : {-1 (start on mid) or 2 or 3 or 4, jump(第幾個位置) or normal(0)}
// -活3跳(2 . 1) 活4跳(3 . 1 or 2 . 2)
// -allPieces[m] = {color(0,1), v(0~7), pos(x,y), link, jump}
//      0  3  5
// v:   1  P  6
//      2  4  7
int checkLink(Position pos, Pieces *linkPieces, int m){
    char color = chessBoard[pos.x][pos.y];
    for(int i=0; i<8; i++){
        int link; // 連線數
        int jump; // 計數是否爲 活x跳
        int f;
        int n = 0;
        // 取得目標向量
        Position v = vL[i];
        // 依向量位移之前座標
        int x = pos.x + v.x;
        int y = pos.y + v.y;
        // 預防 out of range
        if(x < 0 || y < 0 || x > BoardSize-1 || y > BoardSize-1){
            // printf("%02d %02d out of range\n",x,y);
            continue;
        }

        // 連續
        if(colorSame(chessBoard[x][y], color)){
            link = 2; // 連線數
            jump = 0; // 計數是否爲 活x跳
            f = 0;
        }
        // 跳一格
        else if(colorSame(chessBoard[x+v.x][y+v.y], color) && colorSame(chessBoard[x][y], '.')){
            link = 2; // 連線數
            jump = 1; // 計數是否爲 活x跳
            f = 1;
            n = 1;
            x += v.x;
            y += v.y;
        }
        // 空
        else{
            continue;
        }
        
        // 當前位置對角判斷 是否卡中間
        // // FIX: 這裏有問題 沒作用
        Position diagonallyV = vL[7-i];
        int xv = diagonallyV.x, yv = diagonallyV.y;
        if(colorSame(chessBoard[pos.x+xv][pos.y+yv], color)||
        (colorSame(chessBoard[pos.x+xv*2][pos.y+yv*2], color)&&colorSame(chessBoard[pos.x+xv][pos.y+yv], '.'))){
            // printf("%02d %02d mid next!\n",pos.x+1,pos.y+1); // 測試
            continue;
        }
        // printf("%02d %02d,%d\n",pos.x+1,pos.y+1,i);
        // // Fix: 連續數有問題 
        for(int j=0; j<3-n; j++){
            // 更新位置
            x += v.x;
            y += v.y; 
            // 預防 out of range
            if(x < 0 || y < 0 || x > BoardSize-1 || y > BoardSize-1){
                print("out of range\n");
                break;
            }
            // // 有問題得改 10/08
            char nowPiece = chessBoard[x][y];
            // 連續
            if(colorSame(nowPiece, color)){
                print("add\n");
                f = 0;
                link++;
            }
            // 判斷是否活跳
            else if(colorSame(nowPiece, '.') && jump == 0){
                print("jump\n");
                jump = i+1;
                f = 1;
            }
            else if(!colorSame(nowPiece, color) && jump != 0 && f == 1 && n == 0){
                print("連空\n");
                jump = 0;
                break;
            }
            // 不同棋子顏色
            else if(!colorSame(nowPiece, color)){
                print("撞牆\n");
                break;
            } 
        }
        // return
        linkPieces[m].color = color-'0';
        linkPieces[m].v = i;
        linkPieces[m].pos = pos;
        linkPieces[m].link = link;
        linkPieces[m].jump = (jump >= 4) ? 0 : jump;
        m++;
    }
    return m;
}