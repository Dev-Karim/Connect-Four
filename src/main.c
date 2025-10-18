#include <stdio.h>
#include "game.h"

int main(void) {
    int mode = 0, diff = 1;

    puts("Connect Four");
    puts("1) Player vs Player");
    puts("2) Player vs Bot");
    printf("Choose mode (1-2): ");
    if (scanf("%d", &mode) != 1) return 0;

    // eat leftover newline so game input works with fgets
    int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}

    if (mode == 2) {
        puts("Difficulty:");
        puts("  1) Easy  (random valid moves)");
        puts("  2) Medium(win-if-possible, block, center, else random)");
        printf("Choose difficulty (1-2): ");
        if (scanf("%d", &diff) != 1) diff = 1;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        if (diff != 2) diff = 1;
        play_human_vs_bot(diff);
    } else {
        play_human_vs_human();
    }
    return 0;
}
