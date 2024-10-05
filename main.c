#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// 主程式
int main(int argc, char *argv[]){
    // 初始化
    char chessBoard[19][19];
    int i, j, n = 0;
    keyValue anyPiecesL[19*19];
    // argv[1] = "Black" or "White"
    // 判斷當前棋色（黒子 1）（白子 0）
    int target = strcmp(argv[1], "Black") == 0 ? 1 : 0; // strcmp ture is 0
    printf("target : %d\n",target);
    // 接收棋盤 
    for(i=0; i<19; i++){
        for(j=0; j<19; j++){
            scanf(" %c", &chessBoard[i][j]);
            if(chessBoard[i][j] != '.'){
                keyValue l = {i, j, chessBoard[i][j]-'0'};
                anyPiecesL[n] = l;
                n++;
            }
        }
    }

    printf("%d\n",n);
    // 列印子的位置
    for(i=0; i<n; i++){
        pieces target = {anyPiecesL[i].color,0,{anyPiecesL[i].x,anyPiecesL[i].y}};
        printf("x: %d y: %d | %d \n", anyPiecesL[i].x, anyPiecesL[i].y, anyPiecesL[i].color);
        printf("%d|%d\n",i,linkCheck(chessBoard,target));
    }
    // 列印棋盤
    show(chessBoard);
}
