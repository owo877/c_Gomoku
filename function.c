#include <stdio.h>
#include <stdlib.h>
#include "function.h"

// 顯示當前棋盤 error idk
void show(char chessBoard[19][19]){
    int i, j;
    printf("   A B C D E F G H I J K L M N O P Q R S\n");
    for (i=0; i<19; i++){
        printf("%2d ", i + 1);
        for(j=0; j<19; j++){
            printf("%c ", chessBoard[i][j]);
        }
        printf("\n");
    }
}

// 判斷連線數 return {3 or 4, jump or normal}
int linkCheck(char chessBoard[19][19], pieces target){
    // target[2] = {color(0,1), v(0~7), now[2](x,y)}
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
    int nowV[2] = {vL[target.v][0], vL[target.v][1]};
    int x = target.now[1];
    int y = target.now[0];
    int color = target.color;
    int flag = 0;
    int n = 0;
    for(int i = 0 ; i<5; i++){
        if(flag){
            break;
        }
        if((int)(chessBoard[x+nowV[0]][y+nowV[1]] - '0') != color){
            flag = 1;
            return n;
        }
        x += nowV[0];
        y += nowV[1];
        n++;
    }
    return n;
}