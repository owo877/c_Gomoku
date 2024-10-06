#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

const position vL[8] = {
        {-1, -1},
        { 0, -1},
        { 1, -1},
        {-1,  0},
        { 1,  0},
        {-1,  1},
        { 0,  1},
        { 1,  1}
};
// 顯示當前棋盤
void show(char chessBoard[19][19]){
    int i, j;
    printf("\n   A B C D E F G H I J K L M N O P Q R S\n");
    for (i=0; i<19; i++){
        printf("%2d ", i+1);
        for(j=0; j<19; j++){
            printf("%c ", chessBoard[i][j]);
        }
        printf("\n");
    }
}

// 判斷連線數 answer = {3 or 4, jump(1) or normal(0) or None(-1)} 還沒做
// 活3跳(2 . 1) 活4跳(3 . 1 or 2 . 2)
int linkCheck(char chessBoard[19][19], pieces target, int *answer[2]){
    // target = {color(0,1), v(0~7), pos(x,y)}
    //      0  1  2
    // v:   3  A  4
    //      5  6  7
    position v = vL[target.v]; // 取得目標向量
    // 棋子的座標
    position pos = target.pos;
    int color = target.color;
    int link = 0;
    int n = -1; // 計數是否爲 活x跳
    int i;
    
    for(i=0; i<5; i++){
        // 預防 out of range
        if(pos.x < 0 || pos.y < 0 || pos.x > 18 || pos.y > 18){
            break;
        }

        char nowPiece = chessBoard[pos.x+v.x][pos.y+v.y];
        // 判斷是否活跳
        if(nowPiece == "." && n == -1){
            n = 1;
        }
        // 連續
        else if(nowPiece == color){
            pos.x += v.x;
            pos.y += v.y;
            link++;
        }
        // 不同顏色 or 連續爲空
        else{
            // 不連續
            if(i == 1){
                n = 0;
            }
            break;
        }
    }
    // 如果有跳 跳前後連幾？判斷種類？
    answer[0] = link;
    answer[1] = n;
}

void checkVector(char chessBoard[19][19], position pos, int *check){
    int i,n = 0;
    char color = chessBoard[pos.x][pos.y];
    for(i=0; i<8; i++){
        position v = vL[i];
        int x = pos.x + v.x, y = pos.y + v.y;
        // 預防 out of range
        if(x < 0 || y < 0 || x > 18 || y > 18){
            continue;
        }
        else if(chessBoard[x][y] == color){
            check[n] = i;
            n++;
        }
    }
}