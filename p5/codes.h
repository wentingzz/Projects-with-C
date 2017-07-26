/**
    @file bits.h
    @author

    Header file for the bits.c component, with functions supporting
    reading and writing a file a byte at a time and buffering bits for
    codes that extend over byte boundaries.
*/

#include <stdio.h>


/** 
 Given the ASCII code for a character, this function returns the code used to represent it. 
 For example, if you call symToCode( 'A' ), it should return 0x2C. 
 If there's no code to represent the given character, this function returns -1.
 */
int symToCode( unsigned char ch );

/**
 Given the ASCII code for a character, this function returns the the number of bits
 in the code used to represent it. For example, if you call  bitsInCode( 'A' ),
 it should return 6. If there's no code to represent the given character,
 this function returns -1.
 */
int bitsInCode( unsigned char ch );

/**
 Given a code, this function returns the ASCII character it represents.
 For example, if you call codeToSym( 0x2C ), it should return the ASCII code for A.
 If the code does not represent a character, this function returns -1.
 */
int codeToSym( int code );
