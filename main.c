#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "function.h"
int main(int argc, char *argv[]){
    // 初始化
    char chessBoard[19][19];
    int i, j;
    // argv[1] = "Black" or "White"
    // 判斷當前棋色（黒子 1）（白子 0）
    int target = strcmp(argv[1],"Black") ? 1 : 0;
    // 接收棋盤 
    for(i=0; i<19; i++){
        for(j=0; j<19; j++){
            scanf(" %c", &chessBoard[i][j]);
        }
    }






    show(chessBoard);
    return 0;
}

// 顯示當前棋盤
char show(char chessBoard[19][19]){
    int i,j;
    printf("   A B C D E F G H I J K L M N O P Q R S\n");
    for (i=0; i<19; i++){
        printf("%2d ", i + 1);
        for(j=0; j<19; j++){
            printf("%c ", chessBoard[i][j]);
        }
        printf("\n");
    }
}
