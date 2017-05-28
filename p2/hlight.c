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
  putchar( '[' );
  putchar( '3' );
  putchar( '1' );
  putchar( 'm' );
  putchar( ch );
  while ( (ch = getchar()) != '>' ) {
    if (ch == EOF) {
      putchar( '[' );
      putchar( '0' );
      putchar( 'm' );
      exit(0);
    }
    putchar(ch);
  }
  putchar( ch );
  putchar( '[' );
  putchar( '0' );
  putchar( 'm' );
}

/**
  Notices if the entity reaches the end
 */
void showEntity()
{
  putchar( '[' );
  putchar( '3' );
  putchar( '4' );
  putchar( 'm' );
  putchar( ch );
   while ( (ch = getchar()) != ';' ) {
    if (ch == EOF) {
      putchar( '[' );
      putchar( '0' );
      putchar( 'm' );
      exit(0);
    }
    putchar(ch);
  }
  putchar( ch );
  putchar( '[' );
  putchar( '0' );
  putchar( 'm' );
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

