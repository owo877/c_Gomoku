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
// -target : {color(0,1), v(0~7), now[2](x,y), link, jump}
typedef struct {
    int color;
    int v;
    Position pos;
    int link;
    int jump;
} Pieces;

// 控制是否顯示
#define printControl 0
void print(char *str);
// 棋盤大小
#define BoardSize 19
extern char chessBoard[BoardSize][BoardSize];
// 棋子八方向量
extern Position vL[8];
// 顯示棋盤
void show();
// 顏色是否相等
int colorSame(char pieces, char color);
// 確認方向
int checkLink(Position pos, Pieces *allPieces, int m);
// 回傳
void returnAns(Position pos);
// show chess
void showChess(Position pos, Pieces target);