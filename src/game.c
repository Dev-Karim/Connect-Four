// Sprint 1: Two-player Connect Four.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h" 

void play_human_vs_human(void) {
    char board[ROWS][COLS];
    char current = 'A';
    char line[32];

    board_init(board);

    puts("Welcome to Connect Four!");
    puts("Player A: A");
    puts("Player B: B");
    board_print(board);

    while (1) {
        int col_input, row;
        
        printf("Player %c, choose a column (1-7): ", current);
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) {
            clearerr(stdin);
            puts("Invalid move, try again.");
            continue;
        }
        
        col_input = atoi(line);
        if (col_input < 1 || col_input > COLS) {
            puts("Invalid move, try again.");
            continue;
        }

        // drop disc (convert to 0-based column)
        row = board_drop(board, col_input - 1, current);
        if (row < 0) {
            // column full or invalid
            puts("Invalid move, try again.");
            continue;
        }

        // show updated board every valid move
        board_print(board);
        
        if (check_win(board, current)) {
            printf("Player %c wins!\n", current);
            break;
        }

        // draw
        if (board_full(board)) {
            puts("It's a draw!");
            break;
        }

        // next player
        current = (current == 'A') ? 'B' : 'A';
    }
}
