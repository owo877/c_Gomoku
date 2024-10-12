// 宣告檔案

// typedef enum{};
// 儲存座標
typedef struct {
    int x;
    int y;
} position;

// 儲存有棋子的list {座標, 顏色（黑 1, 白 0）}
typedef struct {
    position pos;
    int color;
} keyValue;

// 判斷參數
typedef struct {
    position pos;
    int color;
    int v;
} pieces;

// 控制是否顯示
#define printControl 1
// 顯示棋盤
void show(char chessBorad[19][19]);
// 判斷連線狀態
void linkCheck(char chessBoard[19][19], pieces target, int *answer, int chessVL);
// 確認方向
void checkVector(char chessBoard[19][19], position pos, int *check);