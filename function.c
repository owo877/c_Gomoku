#include <stdio.h>
#include <stdlib.h>
#include "function.h"

// 顯示當前棋盤 error idk
void show(char chessBoard[19][19]){
    int i, j;
    printf("   A B C D E F G H I J K L M N O P Q R S\n");
    for (i=0; i<19; i++){
        printf("%2d ", i+1);
        for(j=0; j<19; j++){
            printf("%c ", chessBoard[i][j]);
        }
        printf("\n");
    }
}

// 判斷連線數 return {3 or 4, jump or normal}
int linkCheck(char chessBoard[19][19], pieces target){
    // target = {color(0,1), v(0~7), now[2](x,y)}
    //      0  1  2
    // v:   3     4
    //      5  6  7
    int vL[8][2] = {
        {-1, -1},
        { 0, -1},
        { 1, -1},
        {-1,  0},
        { 1,  0},
        {-1,  1},
        { 0,  1},
        { 1,  1}};
    int v[2] = {vL[target.v][0], vL[target.v][1]}; // 取得目標向量
    // 棋子的座標
    int x = target.now[1];
    int y = target.now[0];
    int color = target.color;
    int n = 0;
    
    for(int i = 0 ; i<5; i++){
        // 預防out of range
        if(x < 0 || y < 0 || x > 18 || y > 18){
            return n;
        }
        if((int)(chessBoard[x+v[0]][y+v[1]] - '0') != color){
            return n;
        }
        x += v[0];
        y += v[1];
        n++;
    }
    return n;
}