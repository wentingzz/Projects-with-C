/**
  @file jumble.c
  @author Wenting Zheng (wzheng8)
  
  This program is to read in a word list and find word(s) matching the input letters
*/
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

/**
  Program starting point
  
  @return exit status
*/
int main(int argc, char * argv[])
{
  if(argc != 1){
    printf("usage: puzzle <input-file>\n");
    return 1;
  }
  FILE * input = fopen(argv[1], "r");
  if(!input) {
    printf("usage: puzzle <input-file>");
    return 1;
  }
  int row;
  int col;
  int wordCount;
  scanf("%d %d\n%d", &row, &col, &wordCount);
//   prinf("%d\n%d\n%d\n", row, col, word); test
  
  char choice;
  char words[(row > col ? (row + 1):(col + 1))];
  char board[row][col];
  
  int rpos;
  int cpos;
  
  for(int i = 0; i < wordCount; i++){
    scanf("%c %d %d %s", &choice, &rpos, &cpos, words);
    if(choice == 'H'){
      writeHorizontal( rpos, cpos, words, row, col, board);
    } else if (choice == 'V') {
      writeVertical( rpos, cpos, words, row, col, board);
    } else {
      printf("Invalid input");
      return 1;
    }
  }
  printGrid(row, col, board);
  return 0;
}
