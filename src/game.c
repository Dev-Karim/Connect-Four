// Sprint 1: Two-player Connect Four

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"

void play_human_vs_human(void) {
    char board[ROWS][COLS];
    char current = 'A';
    char line[32];

    // initialize and show empty board
    createBoard(board);
    puts("Welcome to Connect Four!");
    puts("Player A: A");
    puts("Player B: B");
    displayBoard(board);

    while (1) {
        int col_input;

        // prompt
        printf("\nPlayer %c, choose a column (1-7): ", current);
        fflush(stdout);

        // read line
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

        // place (convert to 0-based column)
        if (!placeInput(board, col_input - 1, current)) {
            // invalid column index or column is full
            puts("Invalid move, try again.");
            continue;
        }

        // show updated board after every valid move
        displayBoard(board);

        {
            char winner = checkWin(board);
            if (winner == 'A' || winner == 'B') {
                printf("Player %c wins!\n", winner);
                break;
            }
        }

        // draw?
        if (isBoardFull(board)) {
            puts("It's a draw!");
            break;
        }

        // switch player
        current = (current == 'A') ? 'B' : 'A';
    }
}
