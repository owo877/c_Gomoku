#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// 8方向量
const position vL[8] = {
        {-1, -1},
        { -1, 0},
        {-1,  1},
        { 0, -1},
        { 0,  1},
        { 1, -1},
        { 1,  0},
        { 1,  1}
};
void print(char *str){
    if(printControl){
        printf("%s\n",str);
    }
}
// 顯示當前棋盤
void show(char chessBoard[19][19]){
    int i, j;
    // printf("\n   A B C D E F G H I J K L M N O P Q R S\n");
    printf("\n   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
    for (i=0; i<19; i++){
        printf("%2d ", i+1);
        for(j=0; j<19; j++){
            printf("%c ", chessBoard[i][j]);
        }
        printf("\n");
    }
}

// 判斷連線數 answer = {-1 (start on mid) or 2 or 3 or 4, jump(1) or normal(0)} 還沒做
// 活3跳(2 . 1) 活4跳(3 . 1 or 2 . 2)
void linkCheck(char chessBoard[19][19], pieces target, int *answer){
    // target = {color(0,1), v(0~7), pos(x,y)}
    //      0  1  2
    // v:   3  A  4
    //      5  6  7

    // 取得目標向量
    position v = vL[target.v]; 
    // 棋子的座標
    position pos = target.pos;
    int color = target.color;
    int link = -1; // 連線數
    int jump = 0; // 計數是否爲 活x跳
    int i, f = 0;
    
    // 當前位置對角判斷
    position diagonallyV = vL[7-target.v];
    if(chessBoard[pos.x+diagonallyV.x][pos.y+diagonallyV.y] == '0'+color){
        answer[0] = link;
        answer[1] = jump;
        // printf("mid next!\n"); // 測試
        return;
    }
    else{
        link = 1;
    }

    for(i=0; i<5; i++){
        // 預防 out of range
        if(pos.x+v.x < 0 || pos.y+v.y < 0 || pos.x+v.x> 18 || pos.y+v.y > 18){
            print("out of range");
            break;
        }

        // 有問題得改 10/08
        char nowPiece = chessBoard[pos.x+v.x][pos.y+v.y];
        // 連續
        if(nowPiece == '0'+color){
            print("add");
            // printf("add\n");
            link++;
            f = 0;
        }
        // 判斷是否活跳
        else if(nowPiece == '.' && jump == 0){
            print("jump");
            jump = 1;
            f = 1;
        }
        else if(nowPiece == '.' && jump == 1 && f == 1){
            print("連空");
            jump = 0;
            break;
        }
        // 不同顏色
        else if(nowPiece != color){
            print("撞牆");
            break;
        }
        pos.x += v.x;
        pos.y += v.y;
    }
    // 如果有跳 跳前後連幾？判斷種類？
    answer[0] = link;
    answer[1] = jump;
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