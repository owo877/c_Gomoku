#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// 8方向量
const Position vL[8] = {
    {-1, -1},
    { 0, -1},
    { 1, -1},
    {-1,  0},
    { 1,  0},
    {-1,  1},
    { 0,  1},
    { 1,  1}
};
int colorSame(char pieces, int color){
    return pieces == '0'+color;
}
void returnAns(Position pos){
    printf("%c, %d",pos.y+'A',pos.x);
}
void print(char *str){
    if(printControl)printf("%s",str);
}
// show chess
void showChess(Position pos, Pieces target){
    printf("pos : %02d %02d, color : %d, v : %d, link : %d, jump : %d\n", pos.y+1, pos.x+1, target.color, target.v, target.link, target.jump);
}
// 顯示當前棋盤
void show(){
    int i, j;
    // printf("\n   A B C D E F G H I J K L M N O P Q R S | Y\n");
    printf("\n   1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 Y\n");
    for (i=0; i<BoardSize; i++){
        printf("%2d ", i+1);
        for(j=0; j<BoardSize; j++){
            if(chessBoard[i][j] == '0'){
                printf("\x1b[47m\x1b[30m");
            }
            else if(chessBoard[i][j] == '1'){
                printf("\x1b[40m");
            }
            printf("%c", chessBoard[i][j]);
            printf("\x1b[0m ");
        }
        printf("\n");
    }
    printf(" X\n");
}

// 判斷連線數 
// -answer : {-1 (start on mid) or 2 or 3 or 4, jump(1) or normal(0)}
// -活3跳(2 . 1) 活4跳(3 . 1 or 2 . 2)
void linkCheck(Pieces target, int *answer){
    // -target = {color(0,1), v(0~7), pos(x,y)}
    //      0  3  5
    // v:   1  A  6
    //      2  4  7

    // 取得目標向量
    Position v = vL[target.v]; 
    // 棋子的座標
    Position pos = target.pos;
    int color = target.color;
    int link = -1; // 連線數
    int jump = 0; // 計數是否爲 活x跳
    int i, f = 0;
    
    // 當前位置對角判斷 是否卡中間
    Position diagonallyV = vL[7-target.v];
    int xv = diagonallyV.x, yv = diagonallyV.y; 
    if(colorSame(chessBoard[pos.x+xv][pos.y+yv], color)||colorSame(chessBoard[pos.x+xv*2][pos.y+yv*2], color)){
        answer[0] = link;
        answer[1] = jump;
        // printf("mid next!\n"); // 測試
        return;
    }
    else{
        link = 1;
    }

    for(i=0; i<4; i++){
        // 更新位置
        pos.x += v.x;
        pos.y += v.y; 
        // 預防 out of range
        if(pos.x < 0 || pos.y < 0 || pos.x> BoardSize-1 || pos.y > BoardSize-1){
            print("out of range\n");
            break;
        }
        // // 有問題得改 10/08
        char nowPiece = chessBoard[pos.x][pos.y];
        // 連續
        if(colorSame(nowPiece, color)){
            print("add\n");
            f = 0;
            link++;
        }
        // 判斷是否活跳
        else if(nowPiece == '.' && jump == 0){
            print("jump\n");
            jump = i+1;
            f = 1;
        }
        else if(nowPiece == '.' && jump !=0 && f == 1){
            print("連空\n");
            jump = 0;
            break;
        }
        // 不同棋子顏色
        else if(nowPiece != color){
            print("撞牆\n");
            break;
        } 
    }
    // return
    answer[0] = link;
    answer[1] = jump;
}

void checkVector(Position pos, int *check){
    int i = 0;
    char color = chessBoard[pos.x][pos.y];
    for(i=0; i<8; i++){
        Position v = vL[i];
        int x = pos.x + v.x, y = pos.y + v.y;
        // 預防 out of range
        if(x<0 || y<0 || x>BoardSize-1 || y>BoardSize-1){
            continue;
        }
        if(chessBoard[x][y] == color){
            // printf("%d", i);
            check[i] = 1;
        }
    }
}