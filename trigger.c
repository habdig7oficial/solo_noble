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


    /* Start programs logic */

    printf("%s", draw_board(board, DIMENSIONS));

    
    /* Free all memory */

    free_board(board, DIMENSIONS);

    return 0;
}