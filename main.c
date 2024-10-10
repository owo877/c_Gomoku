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
    int nowColor = strcmp(argv[1], "Black") == 0 ? 1 : 0; // strcmp ture is 0
    printf("target : %d\n", nowColor);
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
        position pos = anyPiecesL[i].pos; // 有旗子位置
        // 確認
        printf("x : %d y : %d | color :  %d \n", pos.x+1, pos.y+1, anyPiecesL[i].color);
        // 確認周圍旗子向量 
        int v[8] = {-1,-1,-1,-1,-1,-1,-1,-1}; // 放棄
        checkVector(chessBoard, pos, v);
        for(j=0; j<8; j++){
            if(v[j] == -1){
                // if(i == 0){
                //     printf("單子\n");
                // }
                break;
            }
            // printf("%d ",v[j]); // 向量
            // target = {color(0,1), v(0~7), now[2](x,y)}
            pieces target = {pos, anyPiecesL[i].color, v[j]};
            int type[2]; // 存結果
            linkCheck(chessBoard, target, type);
            if(type[0] == -1){
                // 當前向量卡在中間
                continue;
            }
            printf("連幾顆 : %d | 跳 : %d | 方向 : %d\n", type[0], type[1], v[j]);
        }
        printf("\n");
    }
    // 列印棋盤
    show(chessBoard);
}
