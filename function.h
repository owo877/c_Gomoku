// 宣告檔案

// typedef enum{};

// 顯示棋盤
void show(char chessBorad[19][19]);

// 儲存有棋子的list {座標, 顏色（黑 1, 白 0）} error idk
typedef struct {
    int x;
    int y;
    int color;
}keyValue;