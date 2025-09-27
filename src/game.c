// Sprint 1: Two-player Connect Four game loop + win detection.
// This file handles: turn-taking, input validation, win/draw checks, and printing.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "board.h"
#include "game.h"

// --- Input handling ---------------------------------------------------------

// Reads a column from stdin in the range [1..COLS]. Returns 0..COLS-1 on success, -1 on error.
static int read_column_choice(char player_token) {
    char line[64];

    printf("Player %c, choose a column (1-7): ", player_token);
    fflush(stdout);

    if (!fgets(line, sizeof line, stdin)) {
        // Clear error and signal invalid to re-prompt.
        clearerr(stdin);
        return -1;
    }

    // Newline/Whitespace.
    size_t n = strlen(line);
    while (n && (line[n - 1] == '\n' || line[n - 1] == '\r' || isspace((unsigned char)line[n - 1])))
        line[--n] = '\0';

    // Skip
    char *p = line;
    while (*p && isspace((unsigned char)*p)) p++;

    if (*p == '\0') return -1; // empty

    // Strict integer parse.
    char *end = NULL;
    long val = strtol(p, &end, 10);
    if (end == p || *end != '\0') return -1; // not a pure integer
    if (val < 1 || val > COLS)   return -1; // out of range

    return (int)(val - 1); // convert to 0
}

// --- Win detection ----------------------------------------------------------

static int count_dir(const char b[ROWS][COLS], int r, int c, int dr, int dc, char token) {
    int cnt = 0;
    int rr = r + dr, cc = c + dc;
    while (rr >= 0 && rr < ROWS && cc >= 0 && cc < COLS && b[rr][cc] == token) {
        cnt++;
        rr += dr; cc += dc;
    }
    return cnt;
}

// Fast check centered at the last placed disc (r,c).
static int check_win_lastmove(const char b[ROWS][COLS], int r, int c, char token) {
    // Horizontal
    if (1 + count_dir(b, r, c, 0, -1, token) + count_dir(b, r, c, 0, +1, token) >= 4) return 1;
    // Vertical
    if (1 + count_dir(b, r, c, -1, 0, token) + count_dir(b, r, c, +1, 0, token) >= 4) return 1;
    // Diagonal /
    if (1 + count_dir(b, r, c, -1, +1, token) + count_dir(b, r, c, +1, -1, token) >= 4) return 1;
    // Diagonal \
    if (1 + count_dir(b, r, c, -1, -1, token) + count_dir(b, r, c, +1, +1, token) >= 4) return 1;

    return 0;
}

// --- Game loop --------------------------------------------------------------

void play_human_vs_human(void) {
    char board[ROWS][COLS];
    board_init(board);

    puts("Welcome to Connect Four!");
    puts("Player A: A");
    puts("Player B: B");
    board_print(board);

    char current = 'A';

    for (;;) {
        int col = read_column_choice(current);
        if (col < 0) {
            puts("Invalid move, try again.");
            continue;
        }

        // Attempt to drop the disc; returns row index or -1 if column full/invalid.
        int row = board_drop(board, col, current);
        if (row < 0) {
            puts("Invalid move, try again.");
            continue;
        }

        board_print(board);

        if (check_win_lastmove(board, row, col, current)) {
            printf("Player %c wins!\n", current);
            break;
        }

        if (board_full(board)) {
            puts("It's a draw!");
            break;
        }

        // Next player.
        current = (current == 'A') ? 'B' : 'A';
    }
}
