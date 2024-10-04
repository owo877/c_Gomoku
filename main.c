#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "function.h"

// 主程式
void main(int argc, char *argv[]){
    // 初始化
    char chessBoard[19][19];
    int i, j, n = 0, anyPiecesL[19*19][3];
    // struct keyValue *anyPiecesL; 
    // argv[1] = "Black" or "White"
    // 判斷當前棋色（黒子 1）（白子 0）
    int target = strcmp(argv[1], "Black") == 0 ? 1 : 0; // strcmp ture is 0
    // 接收棋盤 
    for(i=0; i<19; i++){
        for(j=0; j<19; j++){
            scanf(" %c", &chessBoard[i][j]);
            if(chessBoard[i][j] != '.'){
                anyPiecesL[n][0] = i;
                anyPiecesL[n][1] = j;
                anyPiecesL[n][2] = chessBoard[i][j] - '0';
                n++;
            }
        }
    }
    // 列印子的位置
    printf("\n");
    for(i=0; i<n; i++){
        printf("x: %d y: %d | %d \n", anyPiecesL[i][0], anyPiecesL[i][1], anyPiecesL[i][2]);
    }
    // 列印棋盤
    printf("\n");
    printf("   A B C D E F G H I J K L M N O P Q R S\n");
    for (i=0; i<19; i++){
        printf("%2d ", i + 1);
        for(j=0; j<19; j++){
            printf("%c ", chessBoard[i][j]);
        }
        printf("\n");
    }
    // show(chessBoard);
}
// 儲存有棋子的list {座標, 顏色（黑 1, 白 0）} error idk
// struct keyValue{
//     int x, y, color;
// };
// 顯示當前棋盤 error idk
// void show(char chessBoard[19][19]){
//     int i, j;
//     printf("   A B C D E F G H I J K L M N O P Q R S\n");
//     for (i=0; i<19; i++){
//         printf("%2d ", i + 1);
//         for(j=0; j<19; j++){
//             printf("%c ", chessBoard[i][j]);
//         }
//         printf("\n");
//     }
// }
// 判斷連線數
int linkCheck(char chessBoard[19][19], int* target){
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
    int nowV[2] = {vL[target[1]][0], vL[target[1]][1]};
    int x,y = target[2];
    int color = target[0];
    int flag = 0;
    int n = 0;
    for(int i = 0 ; i<5; i++){
        if(flag){
            break;
        }
        if(chessBoard[x+nowV[0]][y+nowV[1]] != color){
            flag = 1;
            return n;
        }
        x += nowV[0];
        y += nowV[1];
        n++;
    }
    return n;
}