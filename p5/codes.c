/**
  @file code.c
  @author Wenting Zheng(wzheng8)

  This program is to help map between symbols and the codes used to represent them.
  It should be efficient, handle large files quickly.
*/
#include <stdio.h>
#include "codes.h"

#define LETTERS_COUNT 26

/**
 Given the ASCII code for a character, this function returns the code used to represent it.
 For example, if you call symToCode( 'A' ), it should return 0x2C.
 If there's no code to represent the given character, this function returns -1.
 */
int symToCode( unsigned char ch )
{
  if (ch == ' ') {
    return 0x5AC;
  } else if (
ch == '\n') {
    return 0x56C;
  } else if (ch >= 'A' && ch <= 'Z') {
    int table[LETTERS_COUNT] = {0x2C, 0x354, 0x6B4, 0xD4, 0x04, 0x2B4, 0x1B4, 0x154, 0x14,
    0xB6C, 0x1AC, 0x2D4, 0x6C, 0x34, 0x36C, 0x5B4, 0xDAC, 0xB4, 0x54, 0xC,
    0xAC, 0x2AC, 0x16C, 0x6AC, 0xD6C, 0x6D4};
    return table[(ch - 'A')];
  }
  return -1;
}

/**
 Given the ASCII code for a character, this function returns the the number of bits
 in the code used to represent it. For example, if you call  bitsInCode( 'A' ),
 it should return 6. If there's no code to represent the given character,
 this function returns -1.
 */
int bitsInCode( unsigned char ch )
{
  if (
ch == ' ' || ch == '\n'){
    return 11;
  } else if (ch >= 'A' && ch <= 'Z') {
    int table[LETTERS_COUNT] = {6, 10, 11, 8, 3, 10, 9, 9, 5, 12, 9, 10, 7, 6, 10, 11, 12,
    8, 7, 4, 8, 10, 9, 11, 12, 11};
    return table[ch - 'A'];
  }
  return -1;
}

/**
 Given a code, this function returns the ASCII character it represents.
 For example, if you call codeToSym( 0x2C ), it should return the ASCII code for A.
 If the code does not represent a character, this function returns -1.
 */
int codeToSym( int code )
{
  if (
code == 0x5AC){
    return ' ';
  } else if (
code == 0x56C) {
    return '\n';
  } else {
    int table[LETTERS_COUNT] = {0x2C, 0x354, 0x6B4, 0xD4, 4, 0x2B4, 0x1B4, 0x154, 0x14,
    0xB6C, 0x1AC, 0x2D4, 0x6C, 0x34, 0x36C, 0x5B4, 0xDAC, 0xB4, 0x54, 0xC,
    0xAC, 0x2AC, 0x16C, 0x6AC, 0xD6C, 0x6D4};
    for(int i = 0; i < LETTERS_COUNT; i++){
      if (
table[i] == code){
        return i + 'A';
      }
    }
  }
  return -1;
}
