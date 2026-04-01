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

    /* Start programs logic */

    char *str = draw_board(board, DIMENSIONS);
    printf("%s", str);
    free(str);
    
    /* Free all memory */

    free_board(board, DIMENSIONS);

    return 0;
}