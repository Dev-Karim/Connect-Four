#include <stdio.h>
#include "board.h"

#define EMPTY_CELL '+'
/*
Board for visualization (6 rows,7 cols):
0 + + + + + + +
1 + + + + + + +
2 + + + + + + +
3 + + + + + + +
4 + + + + + + +
5 + + + + + + +
  0 1 2 3 4 5 6
*/
void createBoard(char board[ROWS][COLS])
{
    for(int i = 0; i <= ROWS; i++) 
    {
        for(int j = 0; j < COLS; j++)
        {
            board[i][j] = EMPTY_CELL;
        }      
    }
}

void displayBoard(char board[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++)
    {
        printf(" ");
        for(int j = 0; j < COLS; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < COLS; i++)
    {
        printf(" %d", i+1);
    }
}

int placeInput(char board[ROWS][COLS], int col, char player)
{
    for(int i = ROWS-1; i >= 0; i--)
    {
        if(board[i][col] == EMPTY_CELL)
        {
            board[i][col] = player;
            return 1;
        }
    }
    return 0;
}

char checkWin(const char board[ROWS][COLS])
{
    // here we are checking horizontally
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j <= COLS-4; j++)
        {
            if(board[i][j] != EMPTY_CELL &&
                 board[i][j] ==  board[i][j+1] &&
                 board[i][j] ==  board[i][j+2] &&
                 board[i][j] == board[i][j+3])
                 return board[i][j];
        }
    }

    // here we are checking vertically
    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j <= ROWS-4; j++)
        {
            if(board[i][j] != EMPTY_CELL &&
                 board[i][j] ==  board[i+1][j] &&
                 board[i][j] ==  board[i+2][j] &&
                 board[i][j] == board[i+3][j])
                 return board[i][j];
        }
    }
    // here we are checking diagonnalLy from top left to bottom right
    // it is better if u draw on a paper the matrix to understand whats happening
    for(int i = 0; i <= ROWS-4; i++)
    {
        for(int j = 0; j <= COLS-4; j++)
        {
            if(board[i][j] != EMPTY_CELL &&
                 board[i][j] ==  board[i+1][j+1] &&
                 board[i][j] ==  board[i+2][j+2] &&
                 board[i][j] == board[i+3][j+3])
                 return board[i][j];
        }
    }
    // we are gonna check from top right to bottom left
    for(int i = 0; i <= ROWS-4; i++)
    {
        for(int j = 3; j < COLS; j++)
        {
            if(board[i][j] != EMPTY_CELL &&
                 board[i][j] ==  board[i+1][j-1] &&
                 board[i][j] ==  board[i+2][j-2] &&
                 board[i][j] == board[i+3][j-3])
                 return board[i][j];
        }
    }

}

int isBoardFull(const char board[ROWS][COLS])
{
    for(int i = 0; i < COLS; i++)
    {
        if(board[0][i] == "+")
            return 0;
    }
    return 1;
}
