#ifndef GAME_H
#define GAME_H

#include "board.h"

// function to start the game loop
void playGame();

// this function is used to give turns for player 'A' or 'B'
char switchPlayer(char currentPlayer);

/*
 get a valid input from the player 
 which will prompt the player to enter a column (1-7)
 then check the input (column is in range and the board is not full) 
 returns index of the columns but need to return the index-1 since an array starts from index 0
*/
int getPlayerMove(char currentPlayer, char board[ROWS][COLS]);

#endif


