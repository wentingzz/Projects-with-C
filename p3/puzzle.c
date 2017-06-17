/**
  @file jumble.c
  @author Wenting Zheng (wzheng8)
  
  This program is to read in a word list and find word(s) matching the input letters
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grid.h"

#define READ_VARS 4
#define MAX_ROW 40
#define MAX_WORD 10

/**
  Program starting point
  
  @return exit status
*/
int main(int argc, char * argv[])
{
  if (argc != 2){
    printf("usage: puzzle <input-file>\n");
    printf("%d", argc);
    return 1;
  }
  FILE * input = fopen(argv[1], "r");
  if (!input) {
    printf("usage: puzzle <input-file>\n");
    fclose(input);
    return 1;
  }
  int row;
  int col;
  int wordCount;
  fscanf(input, "%d %d\n%d\n", &row, &col, &wordCount);
  
  char choice;
  char words[MAX_WORD];
  char board[row][col];
  if (row > MAX_ROW || col > MAX_ROW){
    fprintf(stderr, "Invalid input file\n");
    fclose(input);
    return 1;
  }
  for (int i = 0; i < row; i++){
    for (int j = 0; j < col; j++){
      board[i][j] = '0';
    }
  }
  
  int rpos;
  int cpos;
  for (int i = 0; i < wordCount; i++){
    if (fscanf(input, "%c %d %d %s\n", &choice, &rpos, &cpos, words) != READ_VARS){
      fprintf(stderr, "Invalid input file\n");
      fclose(input);
      return 1;
    }
    if (choice == 'H'){
      if (rpos >= row || (cpos + strlen(words)) > col){
        fprintf(stderr, "Invalid input file\n");
        fclose(input);
        return 1;
      }
      writeHorizontal( rpos, cpos, words, row, col, board);
    } else if ( choice == 'V') {
      if (cpos >= row || (rpos + strlen(words)) > row){
        fprintf(stderr, "Invalid input file\n");
        fclose(input);
        return 1;
      }
      writeVertical( rpos, cpos, words, row, col, board);
    }
  }
  if (board[0][0] == '1'){
    fprintf(stderr, "Invalid input file\n");
    fclose(input);
    return 1;
  }
  printGrid(row, col, board);
  fclose(input);
  return 0;
}
