#include "string.h"


#define DIMENSIONS 7

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

char *draw_board(struct Board board[], int total_len){

    char terminator[] = "____________\n";
    
    char *str = (char *) malloc(total_len * sizeof(char) + total_len + 1 + sizeof(terminator));
    int i_str = 0;
    for(int i = 0; i < total_len; i++, i_str++){
        for(int k = 0; k < board[i].offset; k++, i_str++)
            str[i_str] = ' ';
            
        for(int j = 0; j < board[i].len; j++, i_str++)
           str[i_str] = board[i].row[j]? 'o': '-';
        
        str[i_str] = '\n';
    }
    str[i_str] = '\0';

    strcpy(&str[i_str], terminator);
    return str;
}

void free_board(struct Board board[], int len){
    for(int i = 0; i < len; i++)
        free(board[i].row);
}