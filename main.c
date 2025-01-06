#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

char chessBoard[BoardSize][BoardSize];
Position vL[8];
// 主程式
int main(int argc, char *argv[]){
    // char chessBoard[19][19];
    int i, j, n = 0, m = 0;

    // -存棋子位置 {{x, y}, color}
    // KeyValue anyPiecesL[BoardSize*BoardSize];
    KeyValue *anyPiecesL = malloc(sizeof(KeyValue) * BoardSize * BoardSize);

    // -存是我有連線的棋子
    // Pieces allPieces[BoardSize*BoardSize];
    Pieces *allPieces = malloc(sizeof(Pieces) * BoardSize * BoardSize);

    // -argv[1] = "Black" or "White"
    // -當前棋色（黒子 1）（白子 0）
    int myColor = strcmp(argv[1], "Black") == 0 ? 1 : 0; // strcmp ture is 0
    printf("target color : %d\n", myColor);

    // 接收棋盤 
    for(i=0; i<BoardSize; i++){
        for(j=0; j<BoardSize; j++){
            scanf(" %c", &chessBoard[i][j]);
            if(chessBoard[i][j] != '.'){
                KeyValue l = {{i, j}, chessBoard[i][j]-'0'};
                anyPiecesL[n] = l;
                n++;
            }
        }
    }
    
    // 想減少不必要空間但不會
    // anyPiecesL = (keyValue *)realloc(anyPiecesL, n * sizeof(keyValue));

    printf("場上有幾顆棋子：%d\n\n", n);

    // 判斷個個旗子連續狀態
    for(i=0; i<n; i++){
        Position pos = anyPiecesL[i].pos; // 當前旗子位置座標
        // 確認周圍旗子
        m = checkVector(pos, allPieces, m);
    }

    printf("有多少棋子連線：%d\n", m);
    for(i=0; i<m; i++){
        showChess(allPieces[i].pos, allPieces[i]);
    }

        // for (int k = 4; k > 1; k--){
        //     if(link == k){
        //         if(jump != 0){
        //             // 有活跳
        //             int x = pos.x + vL[j].x * jump;
        //             int y = pos.y + vL[j].y * jump;
        //             printf("可堵下位置（%d 活跳）：%d %d\n", k, x+1, y+1);
        //         }
        //         else{
        //             // 無跳頭或尾
        //             int x = pos.x + vL[j].x * link;
        //             int y = pos.y + vL[j].y * link;
        //             // 確保是空的位子
        //             if(chessBoard[x][y] == '.'){
        //                 printf("可堵下位置（%d）：%d %d\n", k, x+1, y+1);
        //             }
        //             else{
        //                 printf("有牆\n");
        //             }
        //         }
        //     }
        // }
        // printf("\n");
    // }
    
    // 列印棋盤
    show();
    free(anyPiecesL);
    free(allPieces);
}
