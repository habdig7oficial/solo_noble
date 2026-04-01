#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "utils.h"


int main(){
    /* Prepare Board Initial State */
    struct Board board[DIMENSIONS];

    make_min_row(board, DIMENSIONS);

    printf("-------------------\n");

    int skip = make_normal_row(board, DIMENSIONS);

    printf("-------------------\n");

    int inner_len = make_min_row(&board[skip], DIMENSIONS);

    board[DIMENSIONS / 2].row[DIMENSIONS / 2] = true;

    /* Prepare miscellanious */
    FILE *log;
    log = open_log(log);


    /* Start program logic */

    char *draw = (char *) malloc(calc_draw(DIMENSIONS));

    for(int i = 0; i < DIMENSIONS; i++){
        for(int j = 0; board[i].len; j++){
            board[i].row[j] = !board[i].row[j];
            dprint(draw_board(board, DIMENSIONS, draw), log);
            dprint("\n:::::::::::::::\n\n", log);
        }
    }

    /* Free all memory */

    free_board(board, DIMENSIONS);
    free(draw);
    fclose(log);

    return 0;
}