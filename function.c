#include <stdio.h>
#include <stdlib.h>
#include "function.h"

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

// 判斷連線數 return {3 or 4, jump or normal} 還沒做
int linkCheck(char chessBoard[19][19], pieces target){
    // target = {color(0,1), v(0~7), pos(x,y)}
    //      0  1  2
    // v:   3  A  4
    //      5  6  7
    position vL[8] = {
        {-1, -1},
        { 0, -1},
        { 1, -1},
        {-1,  0},
        { 1,  0},
        {-1,  1},
        { 0,  1},
        { 1,  1}};
    position v = vL[target.v]; // 取得目標向量
    // 棋子的座標
    position pos = target.pos;
    int color = target.color;
    int n = 0;
    
    for(int i=0; i<5; i++){
        // 預防out of range
        if(pos.x < 0 || pos.y < 0 || pos.x > 18 || pos.y > 18){
            return n;
        }
        if((int)(chessBoard[pos.x+v.x][pos.y+v.y] - '0') != color){
            return n;
        }
        pos.x += v.x;
        pos.y += v.y;
        n++;
    }
    return n;
}

int checkVector(char chessBoard[19][19], position pos){
    return 0;
}