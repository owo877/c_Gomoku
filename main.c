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
    printf("target : %d\n", target);
    // 接收棋盤 
    for(i=0; i<19; i++){
        for(j=0; j<19; j++){
            scanf(" %c", &chessBoard[i][j]);
            if(chessBoard[i][j] != '.'){
                keyValue l = {{i, j}, chessBoard[i][j]-'0'};
                anyPiecesL[n] = l;
                n++;
            }
        }
    }

    // 確認數量
    // anyPiecesL = (keyValue *)realloc(anyPiecesL, n * sizeof(keyValue)); //想減少不必要空間但不會
    printf("\n%d\n", n);
    // 列印棋子的位置
    for(i=0; i<n; i++){
        int v = 0;
        position pos = anyPiecesL[i].pos;
        // 確認周圍旗子
        v = checkVector(chessBoard, pos);
        // target = {color(0,1), v(0~7), now[2](x,y)}
        pieces target = {anyPiecesL[i].color, v, pos};
        // 確認
        printf("x : %d y : %d | color :  %d \n", pos.x, pos.y, anyPiecesL[i].color);
        printf("連幾顆 : %d | 方向 : %d\n", linkCheck(chessBoard, target), v);
    }
    // 列印棋盤
    show(chessBoard);
}
