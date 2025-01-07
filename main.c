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
    // Pieces linkPieces[BoardSize*BoardSize];
    Pieces *linkPieces = malloc(sizeof(Pieces) * BoardSize * BoardSize);

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
        m = checkLink(pos, linkPieces, m);
    }

    // printf("有多少棋子連線：%d\n", m);
    for(i=0; i<m; i++){
        // 確認用
        showChess(linkPieces[i].pos, linkPieces[i]);
        
        // 判斷所需參數
        Position pos = linkPieces[i].pos;
        int link = linkPieces[i].link;
        int jump = linkPieces[i].jump; // 位置
        int v = linkPieces[i].v;

        // 可下位置判斷
        if(jump != 0){
            int x = pos.x + vL[v].x * jump;
            int y = pos.y + vL[v].y * jump;
            chessBoard[x][y] = '2';
            printf("可堵/下位置（%d 活跳）| %02d %02d\n", link, x+1, y+1);
        }
        else{
            int x = pos.x + vL[v].x * link;
            int y = pos.y + vL[v].y * link;
            // 確保是空的位子
            if(chessBoard[x][y] == '.'){
                chessBoard[x][y] = '3';
                printf("可堵/下位置（%d 連線）| %02d %02d\n", link, x+1, y+1);
            }
            else{
                printf("%02d %02d | 有牆\n",x+1,y+1);  
            }
        }

    printf("\n");
    }
    
    // 列印棋盤
    show();
    free(anyPiecesL);
    free(linkPieces);
}
