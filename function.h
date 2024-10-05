// 宣告檔案

// typedef enum{};

// 儲存有棋子的list {座標, 顏色（黑 1, 白 0）} error idk
typedef struct {
    int x;
    int y;
    int color;
}keyValue;

// 判斷參數
typedef struct {
    int color;
    int v;
    int now[2];
} pieces;

// 顯示棋盤
void show(char chessBorad[19][19]);
//判斷連線狀態
int linkCheck(char chessBoard[19][19],pieces target);