#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define MAX_DEPTH       4
#define INF             1000000
#define MATE_SCORE      100000

typedef struct {
    int from_x, from_y, to_x, to_y;
    char promotion;
    int score;  // for heuristic sorting
} Move;

char board[8][8] = {
    {'r','n','b','q','k','b','n','r'},
    {'p','p','p','p','p','p','p','p'},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P',' ',' ',' ',' ',' ',' ',' '},
    {' ','P','P','P','P','P','P','P'},
    {'R','N','B','Q','K','B','N','R'}
};

int isUpper(char c){return c>='A'&&c<='Z';}
int isLower(char c){return c>='a'&&c<='z';}
int sideToMove = 1; // 1 = white, 0 = black

// piece values
int pieceVal[128];
void initValues(){
    pieceVal['P']=100; pieceVal['N']=320; pieceVal['B']=330;
    pieceVal['R']=500; pieceVal['Q']=900; pieceVal['K']=20000;
    pieceVal['p']=-100; pieceVal['n']=-320; pieceVal['b']=-330;
    pieceVal['r']=-500; pieceVal['q']=-900; pieceVal['k']=-20000;
}

// board evaluation
int evaluate(){
    int s=0;
    for(int i=0;i<8;i++)for(int j=0;j<8;j++){
        s += pieceVal[(int)board[i][j]];
    }
    return s * (sideToMove?1:-1);
}

// find king
void findKing(int isWhite,int *kx,int *ky){
    char k = isWhite? 'K':'k';
    for(int i=0;i<8;i++)for(int j=0;j<8;j++){
        if(board[i][j]==k){*kx=i;*ky=j;return;}
    }
}

// check if square attacked by opponent
// directions for sliding pieces: rook, bishop, queen
const int dirs[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};

int attacked(int x,int y,int byWhite){
    int dx,dy,i,j;
    // pawn attacks
    int dir = byWhite ? -1 : +1;
    for(int dd=-1;dd<=1;dd+=2){
        i = x+dir; j = y+dd;
        if(i>=0&&i<8&&j>=0&&j<8){
            if(board[i][j] == (byWhite?'P':'p')) return 1;
        }
    }
    // knight
    int kx[8]={-2,-2,-1,-1,1,1,2,2}, ky[8]={-1,1,-2,2,-2,2,-1,1};
    for(int k=0;k<8;k++){
        i=x+kx[k]; j=y+ky[k];
        if(i>=0&&i<8&&j>=0&&j<8 &&
           board[i][j] == (byWhite?'N':'n')) return 1;
    }
    // sliding pieces: bishops / queens
    for(int d=0;d<8;d++){
        dx=dirs[d][0]; dy=dirs[d][1];
        for(i=x+dx,j=y+dy;i>=0&&i<8&&j>=0&&j<8;i+=dx,j+=dy){
            char c = board[i][j];
            if(c==' ') continue;
            if(isUpper(c)==byWhite){
                if((d<4 && (c=='R'||c=='Q')) ||
                   (d>=4 && (c=='B'||c=='Q'))) return 1;
            }
            break;
        }
    }
    // kings
    for(dx=-1;dx<=1;dx++)for(dy=-1;dy<=1;dy++){
        if(dx==0&&dy==0) continue;
        i=x+dx;j=y+dy;
        if(i>=0&&i<8&&j>=0&&j<8 && board[i][j]==(byWhite?'K':'k')) return 1;
    }
    return 0;
}

// check if side is in check
int inCheck(int isWhite){
    int x,y;
    findKing(isWhite,&x,&y);
    return attacked(x,y,!isWhite);
}

// generate legal moves and score heuristically
int generateMoves(Move *mlist){
    int count=0;
    for(int x=0;x<8;x++)for(int y=0;y<8;y++){
        char p = board[x][y];
        if(p==' ' || isUpper(p)!=sideToMove) continue;
        int color = sideToMove;
        // pawn moves (no en passant)
        if(toupper(p)=='P'){
            int dir = color? -1 : +1;
            int sx = x+dir;
            if(sx>=0&&sx<8){
                if(board[sx][y]==' '){
                    Move m={x,y,sx,y,' '};
                    if((sx==0||sx==7)){
                        char promotions[] = {'q','r','b','n'};
                        for(int pi=0; pi<4; pi++){
                            char prom = promotions[pi];
                            m.promotion = color ? toupper(prom) : prom;
                            m.score = 900; mlist[count++] = m;
                        }
                    } else {
                        m.score=0; mlist[count++]=m;
                    }
                }
                for(int dy=-1;dy<=1;dy+=2){
                    int sy=y+dy;
                    if(sy>=0&&sy<8 && board[sx][sy] != ' ' &&
                       isUpper(board[sx][sy])!=color){
                        Move m={x,y,sx,sy,' '};
                        m.score = abs(pieceVal[(int)board[sx][sy]]);
                        mlist[count++]=m;
                    }
                }
            }
        }
        // knight
        const int kx[8]={-2,-2,-1,-1,1,1,2,2};
        const int ky[8]={-1,1,-2,2,-2,2,-1,1};
        if(toupper(p)=='N'){
            for(int k=0;k<8;k++){
                int nx=x+kx[k], ny=y+ky[k];
                if(nx>=0&&nx<8&&ny>=0&&ny<8 &&
                   (board[nx][ny]==' ' || isUpper(board[nx][ny])!=color)){
                    Move m={x,y,nx,ny,' '};
                    m.score = board[nx][ny]==' ' ? 0 : abs(pieceVal[(int)board[nx][ny]]);
                    mlist[count++]=m;
                }
            }
        }
        // bishop/rook/queen same sliding code
        char pcs[]="BRQ";
        for(int pi=0;pi<3;pi++){
            char pc = pcs[pi];
            if(toupper(p)!=pc) continue;
            int start = (pi==0?4:(pi==1?0:0));
            int end   = (pi==0?8:(pi==1?4:8));
            for(int d=start;d<end;d++){
                int dx=dirs[d][0], dy=dirs[d][1];
                for(int nx=x+dx,ny=y+dy;nx>=0&&nx<8&&ny>=0&&ny<8;nx+=dx,ny+=dy){
                    if(board[nx][ny]==' '){
                        Move m={x,y,nx,ny,' '};
                        m.score=0; mlist[count++]=m;
                    } else {
                        if(isUpper(board[nx][ny])!=color){
                            Move m={x,y,nx,ny,' '};
                            m.score = abs(pieceVal[(int)board[nx][ny]]);
                            mlist[count++]=m;
                        }
                        break;
                    }
                }
            }
        }
        // king basic
        if(toupper(p)=='K'){
            int dx, dy;
            for(dx=-1;dx<=1;dx++)for(dy=-1;dy<=1;dy++){
                if(dx==0&&dy==0) continue;
                int nx=x+dx, ny=y+dy;
                if(nx>=0&&nx<8&&ny>=0&&ny<8 &&
                   (board[nx][ny]==' '||isUpper(board[nx][ny])!=color)){
                    Move m={x,y,nx,ny,' '};
                    m.score = board[nx][ny]==' ' ? 0 :
                              abs(pieceVal[(int)board[nx][ny]]);
                    mlist[count++]=m;
                }
            }
        }
    }
    return count;
}

// sort moves descending by score
int cmpMove(const void *a, const void *b){
    return ((Move*)b)->score - ((Move*)a)->score;
}

// make / undo
char backup[10000][8][8]; int bcount=0;
void makeMove(Move m){
    memcpy(backup[bcount], board, sizeof board);
    bcount++;
    board[m.to_x][m.to_y] = board[m.from_x][m.from_y];
    board[m.from_x][m.from_y] = ' ';
    if(m.promotion!=' ') board[m.to_x][m.to_y]=m.promotion;
    sideToMove ^= 1;
}
void undoMove(){
    bcount--;
    memcpy(board, backup[bcount], sizeof board);
    sideToMove ^= 1;
}

// quiescence search
int quiesce(int alpha,int beta){
    int stand = evaluate();
    if(stand >= beta) return beta;
    if(alpha < stand) alpha = stand;

    Move moves[256]; int mc=generateMoves(moves);
    qsort(moves, mc, sizeof(Move), cmpMove);
    for(int i=0;i<mc;i++){
        Move *m = &moves[i];
        if(m->score == 0) break;
        makeMove(*m);
        if(inCheck(!sideToMove)){ undoMove(); continue; }
        int val = -quiesce(-beta,-alpha);
        undoMove();
        if(val >= beta) return beta;
        if(val > alpha) alpha = val;
    }
    return alpha;
}
// negamax is a variant of minimax
// negamax with alpha-beta
int negamax(int depth,int alpha,int beta){
    if(depth==0) return quiesce(alpha, beta);

    Move moves[512]; int mc=generateMoves(moves);
    qsort(moves, mc, sizeof(Move), cmpMove);
    if(mc==0){
        if(inCheck(!sideToMove)) return -MATE_SCORE + (MAX_DEPTH-depth);
        return 0; // stalemate
    }

    int best = -INF;
    for(int i=0;i<mc;i++){
        makeMove(moves[i]);
        if(inCheck(!sideToMove)){ undoMove(); continue; }
        int val = -negamax(depth-1, -beta, -alpha);
        undoMove();
        if(val >= beta) return val;
        if(val > best) best = val;
        if(val > alpha) alpha = val;
    }
    return best;
}

// find best move
char *findBest(){
    Move bestm = {0};
    int bestv = -INF;
    Move moves[512];
    int mc = generateMoves(moves);

    qsort(moves, mc, sizeof(Move), cmpMove); // Optional move ordering

    for (int i = 0; i < mc; i++) {
        makeMove(moves[i]);
        if (inCheck(!sideToMove)) {
            undoMove();
            continue;
        }
        int val = -negamax(MAX_DEPTH - 1, -INF, INF);
        undoMove();

        if (val > bestv) {
            bestv = val;
            bestm = moves[i];
        }
    }

    // Apply best move and generate FEN
    makeMove(bestm);
    MakeFen();  //Run FEN generation after making the best move
    undoMove();                 // Clean up state

}

char MakeFen(){
    // Build FEN string
    char fen[128] = {0};
    char temp[16];
    int offset = 0;

    for(int i=0;i<8;i++){
        int empty = 0;
        for(int j=0;j<8;j++){
            char c = board[i][j];
            if(c == ' ') {
                empty++;
            } else {
                if(empty > 0) {
                    offset += sprintf(fen + offset, "%d", empty);
                    empty = 0;
                }
                fen[offset++] = c;
            }
        }
        if(empty > 0) {
            offset += sprintf(fen + offset, "%d", empty);
        }
        if(i != 7) fen[offset++] = '/';
    }

    // Side to move
    offset += sprintf(fen + offset, " %c", sideToMove ? 'w' : 'b');

    // Castling rights (placeholder: none)
    offset += sprintf(fen + offset, " -");

    // En passant (placeholder)
    offset += sprintf(fen + offset, " -");

    // Halfmove clock and fullmove number (placeholders)
    offset += sprintf(fen + offset, " 0 1");

    // Print FEN
    printf("\nFEN: %s\n", fen);

    // Write FEN to file
    FILE *f = fopen("fen.txt", "w");
    if (f) {
        fprintf(f, "%s\n", fen);
        fclose(f);
        printf("FEN written to fen.txt\n");
    } else {
        perror("Error writing to file");
    }
}

void WriteToFile(char *content){

    FILE *file = fopen("fen.txt", "w");  // "w" mode truncates the file if it exists
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fprintf(file, "%s\n", content);  // Write the FEN string to the file
    fclose(file);

    printf("FEN written to fen.txt\n");
}



int main(){
    initValues();
    MakeFen();
    char *fen = findBest();
    printf("\nBest move: %s\n", fen);
    free(fen);
    return 0;
}
