#ifndef BOARD_H
#define BOARD_H

#define ROWS 6
#define COLS 7

// function to create the board 
void createBoard(char board[ROWS][COLS]);

// used to display the board on the terminal 
void displayBoard(char board[ROWS][COLS]);

/*
 function used to place the input from the player 'A' or 'B' and the collumn specified from the player
 we return 1 if it is successfull and 0 otherwise
*/
int placeInput(char board[ROWS][COLS], int col, char player);

/*
 pretty self explanatory we want to check if a player has won
 if a player placed 4 in a row either horizontally, vertically, diagonally
 we return 'A' if player A wins and return 'B' if player B wins and if none won
 we return ' '
*/
char checkWin(char board[ROWS][COLS]);

/* 
here we want to check if the board is full 
because if its full that indicates that its a draw
we return 1 if its full and 0 if not
*/
int isBoardFull(char board[ROWS][COLS]);

#endif
