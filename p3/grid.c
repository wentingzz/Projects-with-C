/**
  @file jumble.c
  @author Wenting Zheng (wzheng8)
  
  This program is to read in a word list and find word(s) matching the input letters
*/
#include <stdio.h>
#include <stdlib.h>
// #include "grid.h"

/**
  adds a word to the grid with the first letter at row rpos and column cpos with a horizontal orientation
  
  @param rpos row of the first letter of the word to add
  @param cpos column of the first letter of the word to add
  @param word[] word to add
  @param rows number of rows in the grid
  @param cols number of columns in the grid
  @param grid[rows][cols] represents the board
*/
void writeHorizontal( int rpos, int cpos, char word[], int rows, int cols, char grid[ rows ][ cols ] )
{
  int count = 0;
  for (int i = cpos; i < cols; i++){
    if (word[count] == '\0'){
      break;
    }
    grid[rpos][i] = word[count++];
  }
}

/**
  adds a word to the grid with the first letter at row rpos and column
  cpos with a vertical orientation
  
  @param rpos row of the first letter of the word to add
  @param cpos column of the first letter of the word to add
  @param word[] word to add
  @param rows number of rows in the grid
  @param cols number of columns in the grid
  @param grid[rows][cols] represents the board
*/
void writeVertical( int rpos, int cpos, char word[], int rows, int cols, char grid[ rows ][ cols ] )
{
  int count = 0;
  for (int i = rpos; i < rows; i++){
    if (word[count] == '\0'){
      break;
    }
    grid[i][cpos] = word[count++];
  }
}

/**
  prints the given grid (of the given rows/cols size) to standard output
  in the for (mat described in the requirements
  
  @param rows rows of the grid
  @param cols columns of the grid
  @param board[rows][cols]
*/
void printGrid( int rows, int cols, char board[ rows ][ cols ] )
{
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols - 1; j++){
      if (board[i][j] < 'A' || board[i][j] > 'Z'){
        board[i][j] = ' ';
      }
      printf("%c ", board[i][j]);
    }
    if (board[i][cols - 1] < 'A' || board[i][cols - 1] > 'Z'){
        board[i][cols - 1] = ' ';
    }
    printf("%c\n", board[i][cols - 1]);
  }
}
