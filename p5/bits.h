/**
    @file bits.h
    @author

    Header file for the bits.c component, with functions supporting
    reading and writing a file a byte at a time and buffering bits for
    codes that extend over byte boundaries.
*/

#ifndef _BITS_H_
#define _BITS_H_

#include <stdio.h>

/** Number of bits per byte.  This isn't going to change, but it lets us give
    a good explanation instead of just the literal value, 8. */
#define BITS_PER_BYTE 8

/** Buffer space for up to 8 bits that have been written by the
    application but haven't yet been written out to a file, or that
    have been read from a file but not yet used by the application.
    When this structure is initialized, zeros should be stored in both
    fields.
*/
typedef struct {
  /** Storage for up to 8 bits left over from an earlier read or waiting
      to be written in a subsequent write. */
  unsigned char bits;

  /** Number of bits currently buffered. */
  int bcount;
} BitBuffer;

/** Write the code stored in the code parameter.  Temporarily
    store bits in the given buffer until we have 8 of them and can
    write them to the file.
    @param code to write out
    @param nbits number of bits in code
    @param buffer pointer to storage for bits that can't be written to the
    file yet.  When this function is called, this buffer may already
    contain some bits left-over from a previous write.
    @param fp file we're writing to, opened for writing in binary mode.
*/
void writeBits( int code, int nbits, BitBuffer *buffer, FILE *fp );


/** If there are any bits buffered in buffer, write them out to the
    given file in the high-order bit positions of a byte, leaving zeros
    in the low-order bits.
    @param buffer pointer to storage for unwritten bits left over
    from a previous write.
    @param fp file these bits are to be written to, opened for writing
    in binary mode
*/
void flushBits( BitBuffer *buffer, FILE *fp );


/** Reads and returns the next valid code from the given file. Each valid code
    starts with a 1 and ends with two consecutive 0s (00).
    if no bits or only 0s have been read when the end of file is reached,
    -1 is returned.
    If the first bit read is a 1 and the end of file is reached before
    two consecutive 0s (00) are read, -2 is returned.
    If the first bit read is a 0 and a 1 is read before the end of the file
    is reached, -2 is returned.
    The given buffer may contain some bits left over from the last read, and if this
    the read has any left-over bits, it should leave them in that buffer.
    @param buffer pointer to storage for left-over from one read call to the
    next.
    @param fp file bits are being read from, opened for reading in binary.
    @return value of the valid code read in, -1 if we reach the
    end-of-file under valid conditions, and -2 if the file is invalid.
*/
int readBits (BitBuffer *buffer, FILE *fp );

#endif
