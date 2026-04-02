#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "utils.h"

/* 
    Felipe Mendonça Garbelotti - 10723734
    Mateus Felipe da Silveira Vieira - 10723904
*/

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

    solve(board, DIMENSIONS, 31, draw, log);


    

    /*

    */

    dprint(draw_board(board, DIMENSIONS, draw), log);

    /* Free all memory */

    free_board(board, DIMENSIONS);
    free(draw);
    fclose(log);

    return 0;
}