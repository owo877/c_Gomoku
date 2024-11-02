// 宣告檔案
// typedef enum{};
// 儲存座標
typedef struct {
    int x;
    int y;
} Position;

// 儲存有棋子的list {座標, 顏色（黑 1, 白 0）}
typedef struct {
    Position pos;
    int color;
} KeyValue;

// 判斷參數
typedef struct {
    Position pos;
    int color;
    int v;
    int link;
    int jump;
} Pieces;

// 控制是否顯示
#define printControl 0
// 顯示棋盤
void show(char chessBorad[19][19]);
// 判斷連線狀態
void linkCheck(char chessBoard[19][19], Pieces target, int *answer);
// 確認方向
void checkVector(char chessBoard[19][19], Position pos, int *check);