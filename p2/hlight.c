/**
   @file hlight.c
   @author Wenting Zheng (wzheng8)
   
   this program is to read text from standard input and output identical text with HTML
   tags colored red and HTML entities colored blue
 */

#include <stdio.h>
#include <stdlib.h>

/** current character to process*/
int ch;

/**
  Notices if the tag reaches the end and handles error if the file ends before the > sign
 */
void showTag()
{
  printf("\e[31m<");
  while ( (ch = getchar()) != '>' ) {
    if (ch == EOF) {
      printf("\e[0m");
      exit(0);
    }
    putchar(ch);
  }
  printf(">\e[0m");
}

/**
  Notices if the entity reaches the end
 */
void showEntity()
{
  printf("\e[34m&");
   while ( (ch = getchar()) != ';' ) {
    if (ch == EOF) {
      printf("\e[0m");
      exit(0);
    }
    putchar(ch);
  }
  printf(";\e[0m");
}

/**
  Program starting point, reads character in the input file until the end
  
  @return program exit status
*/
int main()
{
  while ( (ch = getchar() ) != EOF ) {
    if (ch == '<' ) { //starting the tag
      showTag();
    } else if ( ch == '&' ) { //starting the entity
      showEntity();
    } else {
      putchar( ch );
    }
  }
  return EXIT_SUCCESS;
}