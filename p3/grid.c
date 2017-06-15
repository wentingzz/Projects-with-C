/**
  @file jumble.c
  @author Wenting Zheng (wzheng8)
  
  This program is to read in a word list and find word(s) matching the input letters
*/
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

/**
  adds a word to the grid with the first letter at row rpos and column cpos with a horizontal orientation
  
  @param rpos row of the first letter of the word to add
  @param cpos column of the first letter of the word to add
  @param word[] word to add
  @param rows 
  @param cols 
  @param grid[rows][cols]
*/
void writeHorizontal( int rpos, int cpos, char word[], int rows, int cols, char grid[ rows ][ cols ] )
{

}

/**
  adds a word to the grid with the first letter at row rpos and column cpos with a vertical orientation
  
  @param rpos row of the first letter of the word to add
  @param cpos column of the first letter of the word to add
  @param word[] word to add
  @param rows
  @param cols
  @param grid[rows][cols]
*/
void writeVertical( int rpos, int cpos, char word[], int rows, int cols, char grid[ rows ][ cols ] )
{

}

/**
  prints the given grid (of the given rows/cols size) to standard output in the format described in the requirements
  
  @param rows rows of the grid
  @param cols columns of the grid
  @param board[rows][cols]
*/
void printGrid( int rows, int cols, char board[ rows ][ cols ] )
{

}