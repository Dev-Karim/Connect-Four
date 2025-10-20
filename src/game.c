// Sprint 2: add Human vs Bot with difficulty levels (Easy, Medium).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "board.h"

static int read_column_input(char player) {
    char line[32];
    int col_input;

    printf("\nPlayer %c, choose a column (1-7): ", player);
    fflush(stdout);

    if (!fgets(line, sizeof(line), stdin)) {
        clearerr(stdin);
        puts("Invalid move, try again.");
        return -1;
    }

    col_input = atoi(line);
    if (col_input < 1 || col_input > COLS) return -1;
    return col_input - 1;
}
void play_human_vs_human(void) {
    char board[ROWS][COLS];
    char current = 'A';

    createBoard(board);
    puts("Welcome to Connect Four!");
    puts("Player A: A");
    puts("Player B: B");
    displayBoard((const char (*) [COLS]) board);

    while (1) {
        int col = read_column_input(current);
        if (col < 0 || !placeInput(board, col, current)) {
            puts("Invalid move, try again.");
            continue;
        }

        displayBoard((const char (*) [COLS]) board);

        {
            char winner = checkWin((const char (*) [COLS]) board);
            if (winner == 'A' || winner == 'B') {
                printf("Player %c wins!\n", winner);
                break;
            }
        }

        if (isBoardFull((const char (*) [COLS]) board)) {
            puts("It's a draw!");
            break;
        }

        current = (current == 'A') ? 'B' : 'A';
    }
}
static int column_has_space(const char b[ROWS][COLS], int c) {
    if (c < 0 || c >= COLS) return 0;
    return b[0][c] == '+';
}
static int find_row_for_col(const char b[ROWS][COLS], int c) {
    if (c < 0 || c >= COLS) return -1;
    for (int r = ROWS - 1; r >= 0; r--) {
        if (b[r][c] == '+') return r;
    }
    return -1;
}
static void copy_board(char dst[ROWS][COLS], const char src[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            dst[r][c] = src[r][c];
}
static char simulate_winner_if_drop(const char b[ROWS][COLS], int c, char token) {
    char tmp[ROWS][COLS];
    copy_board(tmp, b);
    int row = find_row_for_col((const char (*)[COLS]) tmp, c);
    if (row < 0) return '\0';
    tmp[row][c] = token;
    return checkWin((const char (*)[COLS]) tmp);
}
static int bot_choose_random_col(const char b[ROWS][COLS]) {
    int valid[COLS], n = 0;
    for (int c = 0; c < COLS; c++) {
        if (column_has_space(b, c)) valid[n++] = c;
    }
    if (n == 0) return -1;
    int pick = rand() % n;
    return valid[pick];
}

// Medium
static int bot_choose_medium_col(const char b[ROWS][COLS], char bot, char human) {
    for (int c = 0; c < COLS; c++) {
        if (column_has_space(b, c) && simulate_winner_if_drop(b, c, bot) == bot)
            return c;
    }

    for (int c = 0; c < COLS; c++) {
        if (column_has_space(b, c) && simulate_winner_if_drop(b, c, human) == human)
            return c;
    }
    int order[COLS] = {3,4,2,5,1,6,0};
    for (int i = 0; i < COLS; i++) {
        int c = order[i];
        if (column_has_space(b, c)) return c;
    }

    return bot_choose_random_col(b);
}

void play_human_vs_bot(int difficulty) {
    char board[ROWS][COLS];
    char human = 'A';
    char bot   = 'B';
    char current = human;

    srand((unsigned)time(NULL));

    createBoard(board);
    puts("Welcome to Connect Four!");
    puts("Player A (Human): A");
    puts("Player B (Bot):   B");
    displayBoard((const char (*)[COLS]) board);

    while (1) {
        int col = -1;

        if (current == human) {
            // human move
            col = read_column_input(human);
            if (col < 0 || !placeInput(board, col, human)) {
                puts("Invalid move, try again.");
                continue;
            }
        } else {
            // bot move
            if (difficulty == 2) {
                col = bot_choose_medium_col((const char (*)[COLS]) board, bot, human);
            } else {
                col = bot_choose_random_col((const char (*)[COLS]) board);
            }
            if (col < 0 || !placeInput(board, col, bot)) {
                // should not happen
                for (int c = 0; c < COLS; c++) {
                    if (placeInput(board, c, bot)) { col = c; break; }
                }
            }
            printf("\nBot (B) plays column %d\n", col + 1);
        }
        displayBoard((const char (*)[COLS]) board);

        // winner
        {
            char winner = checkWin((const char (*)[COLS]) board);
            if (winner == 'A' || winner == 'B') {
                printf("Player %c wins!\n", winner);
                break;
            }
        }

        // draw
        if (isBoardFull((const char (*)[COLS]) board)) {
            puts("It's a draw!");
            break;
        }

        // next turn
        current = (current == human) ? bot : human;
    }
}
