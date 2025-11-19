#include <stdio.h>
#include "game.h"

int main(void) {
    int mode = 0, diff = DIFF_EASY;

    puts("Connect Four");
    puts("1) Player vs Player");
    puts("2) Player vs Bot");
    printf("Choose mode (1-2): ");
    if (scanf("%d", &mode) != 1) return 0;

    int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (mode == 2) {
        puts("Difficulty:");
        puts("  1) Easy   (random valid moves)");
        puts("  2) Medium (win/block + center)");
        puts("  3) Hard   (minimax + alpha-beta)");
        printf("Choose difficulty (1-3): ");
        if (scanf("%d", &diff) != 1) diff = DIFF_EASY;
        while ((ch = getchar()) != '\n' && ch != EOF) {}

        if (diff < DIFF_EASY || diff > DIFF_HARD) diff = DIFF_EASY;

        play_human_vs_bot(diff);
    } else {
        play_human_vs_human();
    }
    return 0;
}
