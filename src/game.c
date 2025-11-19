#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include "board.h"
#include "game.h"

#define INF 1000000000
#define HARD_SEARCH_DEPTH 6

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

/* ---------- Hard-level bot (Sprint 4) ---------- */

static int evaluate_window(char a, char b, char c, char d, char bot, char human) {
    int bot_count = 0, human_count = 0, empty_count = 0;

    char w[4] = {a, b, c, d};
    for (int i = 0; i < 4; i++) {
        if (w[i] == bot) bot_count++;
        else if (w[i] == human) human_count++;
        else if (w[i] == '+') empty_count++;
    }

    int score = 0;
    if (bot_count == 4) score += 1000;
    else if (bot_count == 3 && empty_count == 1) score += 50;
    else if (bot_count == 2 && empty_count == 2) score += 10;

    if (human_count == 3 && empty_count == 1) score -= 80;
    else if (human_count == 2 && empty_count == 2) score -= 10;

    return score;
}

static int evaluate_position(const char b[ROWS][COLS], char bot, char human) {
    int score = 0;

    int center_col = COLS / 2;
    int center_count = 0;
    for (int r = 0; r < ROWS; r++) {
        if (b[r][center_col] == bot) center_count++;
    }
    score += center_count * 3;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            score += evaluate_window(
                b[r][c], b[r][c+1], b[r][c+2], b[r][c+3], bot, human);
        }
    }

    for (int c = 0; c < COLS; c++) {
        for (int r = 0; r <= ROWS - 4; r++) {
            score += evaluate_window(
                b[r][c], b[r+1][c], b[r+2][c], b[r+3][c], bot, human);
        }
    }

    for (int r = 0; r <= ROWS - 4; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            score += evaluate_window(
                b[r][c], b[r+1][c+1], b[r+2][c+2], b[r+3][c+3], bot, human);
        }
    }

    for (int r = 0; r <= ROWS - 4; r++) {
        for (int c = 3; c < COLS; c++) {
            score += evaluate_window(
                b[r][c], b[r+1][c-1], b[r+2][c-2], b[r+3][c-3], bot, human);
        }
    }

    return score;
}

static int minimax(char b[ROWS][COLS],
                   int depth,
                   int maximizing,
                   char bot,
                   char human,
                   int alpha,
                   int beta) {
    char winner = checkWin((const char (*)[COLS]) b);
    if (winner == bot)   return 100000 + depth;
    if (winner == human) return -100000 - depth;

    if (depth == 0 || isBoardFull((const char (*)[COLS]) b)) {
        return evaluate_position((const char (*)[COLS]) b, bot, human);
    }

    int order[COLS] = {3,4,2,5,1,6,0};

    if (maximizing) {
        int best = -INF;
        for (int i = 0; i < COLS; i++) {
            int c = order[i];
            if (!column_has_space((const char (*)[COLS]) b, c)) continue;

            int row = find_row_for_col((const char (*)[COLS]) b, c);
            b[row][c] = bot;

            int val = minimax(b, depth - 1, 0, bot, human, alpha, beta);

            b[row][c] = '+';

            if (val > best) best = val;
            if (val > alpha) alpha = val;
            if (beta <= alpha) break;
        }
        return best;
    } else {
        int best = INF;
        for (int i = 0; i < COLS; i++) {
            int c = order[i];
            if (!column_has_space((const char (*)[COLS]) b, c)) continue;

            int row = find_row_for_col((const char (*)[COLS]) b, c);
            b[row][c] = human;

            int val = minimax(b, depth - 1, 1, bot, human, alpha, beta);

            b[row][c] = '+';

            if (val < best) best = val;
            if (val < beta) beta = val;
            if (beta <= alpha) break;
        }
        return best;
    }
}

/* multithreaded (Bonus) */

typedef struct {
    char board[ROWS][COLS];
    char bot;
    char human;
    int depth;
    int col;
    int score;
} MinimaxJob;

static void *thread_minimax_run(void *arg) {
    MinimaxJob *job = (MinimaxJob *)arg;
    job->score = minimax(job->board, job->depth, 0, job->bot, job->human, -INF, INF);
    return NULL;
}

static int bot_choose_hard_col(const char b[ROWS][COLS], char bot, char human) {
    int valid[COLS];
    int moves = 0;

    for (int c = 0; c < COLS; c++) {
        if (column_has_space(b, c)) {
            valid[moves++] = c;
        }
    }
    if (moves == 0) return -1;

    pthread_t threads[COLS];
    MinimaxJob jobs[COLS];

    for (int i = 0; i < moves; i++) {
        int c = valid[i];

        jobs[i].bot = bot;
        jobs[i].human = human;
        jobs[i].depth = HARD_SEARCH_DEPTH - 1;
        jobs[i].col = c;

        copy_board(jobs[i].board, b);
        int row = find_row_for_col((const char (*)[COLS]) jobs[i].board, c);
        if (row < 0) {
            jobs[i].score = -INF;
            continue;
        }
        jobs[i].board[row][c] = bot;

        pthread_create(&threads[i], NULL, thread_minimax_run, &jobs[i]);
    }

    for (int i = 0; i < moves; i++) {
        pthread_join(threads[i], NULL);
    }

    int best_col = valid[0];
    int best_score = jobs[0].score;

    for (int i = 1; i < moves; i++) {
        if (jobs[i].score > best_score) {
            best_score = jobs[i].score;
            best_col = valid[i];
        }
    }

    return best_col;
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
            col = read_column_input(human);
            if (col < 0 || !placeInput(board, col, human)) {
                puts("Invalid move, try again.");
                continue;
            }
        } else {
            if (difficulty == DIFF_HARD) {
                col = bot_choose_hard_col((const char (*)[COLS]) board, bot, human);
            } else if (difficulty == DIFF_MEDIUM) {
                col = bot_choose_medium_col((const char (*)[COLS]) board, bot, human);
            } else {
                col = bot_choose_random_col((const char (*)[COLS]) board);
            }

            if (col < 0 || !placeInput(board, col, bot)) {
                for (int c = 0; c < COLS; c++) {
                    if (placeInput(board, c, bot)) { col = c; break; }
                }
            }
            printf("\nBot (B) plays column %d\n", col + 1);
        }
        displayBoard((const char (*)[COLS]) board);

        {
            char winner = checkWin((const char (*)[COLS]) board);
            if (winner == 'A' || winner == 'B') {
                printf("Player %c wins!\n", winner);
                break;
            }
        }

        if (isBoardFull((const char (*)[COLS]) board)) {
            puts("It's a draw!");
            break;
        }

        current = (current == human) ? bot : human;
    }
}
