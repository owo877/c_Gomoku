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
