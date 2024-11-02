#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

char chessBoard[BoardSize][BoardSize];
// 主程式
int main(int argc, char *argv[]){
    // char chessBoard[19][19];
    int i, j, n = 0, m = 0;
    // -存棋子位置 {{x, y}, color}
    KeyValue anyPiecesL[BoardSize*BoardSize]; 
    // -存是我有有機會活四連線
    Pieces allPieces[BoardSize*BoardSize];
    // -argv[1] = "Black" or "White"
    // -當前棋色（黒子 1）（白子 0）
    int nowColor = strcmp(argv[1], "Black") == 0 ? 1 : 0; // strcmp ture is 0
    printf("target color : %d\n", nowColor);

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
        // 確認周圍旗子向量 
        int v[8] = {-1,-1,-1,-1,-1,-1,-1,-1}; // 先這樣沒降法
        checkVector(pos, v);
        // 確認個向量棋子是否連續
        for(j=0; j<8; j++){
            // 爲空
            if(v[j] == -1)continue;
            // -target : {color(0,1), v(0~7), now[2](x,y), link, jump}
            // -type : {link, jump}
            Pieces target = {pos, anyPiecesL[i].color, j};
            int type[2]; // 存結果
            linkCheck(target, type);
            if(type[0] == -1){
                // 當前向量卡在中間
                continue;
            }
            target.jump = type[0];
            target.link = type[1];
            allPieces[m] = target;
            // 確認用
            printf("\x1b[91m");
            printf("x: %02d y: %02d | color: %d\n", pos.x+1, pos.y+1, anyPiecesL[i].color);
            printf("\x1b[0m");

            printf("\x1b[96m");
            printf("連幾顆: %d | 跳第: %d | 方向: %d\n\n", allPieces[m].jump, allPieces[m].link, j);
            printf("\x1b[0m");

            m++;            
        }

        // 判斷下棋點
        
    }
    // 列印棋盤
    show();
}
