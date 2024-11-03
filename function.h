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
void print(char *str);
// 棋盤大小
#define BoardSize 19
extern char chessBoard[BoardSize][BoardSize];
// 顯示棋盤
void show();
// 顏色是否相等
int colorSame(char pieces, int color);
// 判斷連線狀態
void linkCheck(Pieces target, int *answer);
// 確認方向
void checkVector(Position pos, int *check);
// 回傳
void returnAns(Position pos);