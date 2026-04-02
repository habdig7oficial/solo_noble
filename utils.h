#include "string.h"
#include "time.h"

#define CHAR_NAME 30
#define DIMENSIONS 7

#define AXIS_Y true
#define AXIS_X false

#define FORWARD true
#define BACKWARD false

#define IS_EMPTY true
#define NOT_EMPTY false

/* Make Board */
struct Board {
    bool *row;
    int len;
    int offset; 
};


int make_min_row(struct Board board[], int len){
    int internal = (len / 2) / 2 + len % 2;
    for(int i = 0; i < internal; i++){
        board[i].len = (len / 2);
        board[i].row = (bool *) malloc(board[i].len * sizeof(int));
        board[i].offset = internal;
        //printf("%p - %d - %d\n", board[i].row, board[i].len, board[i].offset);
    }
    return internal;
}

int make_normal_row(struct Board board[], int len){
    int skip = (len / 2) / 2 + len % 2;
    int stop_at = len - skip;
    for(int i = skip; i < stop_at; i++){
        board[i].len = len;
        board[i].row = (bool *) malloc(board[i].len * sizeof(int));
        board[i].offset = 0;
        //printf("%p - %d - %d\n", board[i].row, board[i].len, board[i].offset);
    }
    return stop_at;
}

int calc_draw(int total_len){
    return (total_len * total_len + total_len + 1) * sizeof(char);
}

char *draw_board(struct Board board[], int total_len, char *str){
    //char *str = (char *) malloc(total_len * sizeof(char) + total_len + 1 + sizeof(terminator));
    int i_str = 0;
    for(int i = 0; i < total_len; i++, i_str++){
        for(int k = 0; k < board[i].offset; k++, i_str++)
            str[i_str] = ' ';
            
        for(int j = 0; j < board[i].len; j++, i_str++)
           str[i_str] = board[i].row[j]? '-': 'x';
        
        str[i_str] = '\n';
    }
    str[i_str] = '\0';
    return str;
}

void free_board(struct Board board[], int len){
    for(int i = 0; i < len; i++)
        free(board[i].row);
}


/* Handle FILE */

FILE *open_log(FILE *log){
    time_t now;
    time(&now);

    char name[CHAR_NAME];
    
    sprintf(name, "./log/log_%ld.txt", (long) now);

    log = fopen(name, "w");

    return log;
}

void dprint(char *msg, FILE *log){
    printf("%s", msg);
    fprintf(log, "%s", msg);
}

bool move(struct Board board[], int total_len, int x, int y, bool axis, bool sense){
    short invy = (axis == AXIS_Y) ? -1 : 1;
    short vsense = (sense == FORWARD ? 2 : -2)  * invy;
    short vbefore = (sense == FORWARD ? 1 : -1) * invy;

    /* Precheck if position is in range*/
    if(y >= total_len || x >= board[y].len)
        return false;
    else if(axis == AXIS_X && x + vsense >= board[y].len)
        return false;
    else if(axis == AXIS_Y && y + vsense >= total_len)
        return false;

    /* Check if tile is already empty */
    else if(board[y].row[x] == IS_EMPTY)
        return false;

    int offset = 0;
    if(axis == AXIS_Y)
        offset = board[y].offset - board[y + vsense].offset;

    
    /* Check if the destination is not empty */
    if(axis == AXIS_X && board[y].row[x + vsense] == NOT_EMPTY)
        return false;
    else if(axis == AXIS_Y && board[y + vsense].row[x + offset] == NOT_EMPTY)
        return false;

    board[y].row[x] = IS_EMPTY;

    if(axis == AXIS_X){
        board[y].row[x + vsense] = NOT_EMPTY;
        board[y].row[x + vbefore] = IS_EMPTY;
    }
    else{
        board[y + vsense].row[x + offset] = NOT_EMPTY;
        board[y + vbefore].row[x + offset] = IS_EMPTY;
    }


    board[y].row[x] = IS_EMPTY;

    printf("(%d, %d) -> (%d, %d)\n", x, y, x + (axis == AXIS_X) ? vsense : 0, y + (axis == AXIS_Y) ? vsense : 0);
    return true;
}

bool undo(struct Board board[], int total_len, int x, int y, bool axis, bool sense){

}


/* Backtracking function */

bool solve(struct Board board[], int len, char *draw, FILE *log){
    for(int i = 0; i < len; i++){
        for(int j = 0; j < board[i].len; j++){
            bool res;
            bool save_state; 
            
            save_state = board[i].row[j + 1];
            if(move(board, len, i, j, AXIS_X, FORWARD)){
                // call recursive
                move(board, len, i, j + 2, AXIS_X, BACKWARD);
                board[i][j + 1] = save_state;
            }
            save_state = board[i][j - 1];
            if(move(board, len, i, j, AXIS_X, BACKWARD)){

            }

            save_state = board[i + 1][j];
            if(move(board, len, i, j, AXIS_Y, FORWARD)){

            }
            save_state = board[i - 1][j];
            if(move(board, len, i, j, AXIS_Y, BACKWARD)){

            }

            dprint(draw_board(board, len, draw), log);
            dprint("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n", log);
        }
    }
}