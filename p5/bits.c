/**
  @file bits.c
  @author Wenting Zheng(wzheng8)
  
  This program defines functions for writing out bit sequences to and from a file.
  It is to read and write the bit codes needed for encryption/decryption.
*/
#include <stdio.h>
#include "bits.h"

#define BITS_MAX 8
#define MAS_LENGTH 13

/** Write the code stored in the code parameter.  Temporarily
    store bits in the given buffer until we have BITS_MAX of them and can
    write them to the file.
    @param code to write out
    @param nbits number of bits in code
    @param buffer pointer to storage for bits that can't be written to the
    file yet.  When this function is called, this buffer may already
    contain some bits left-over from a previous write.
    @param fp file we're writing to, opened for writing in binary mode.
*/
void writeBits( int code, int nbits, BitBuffer *buffer, FILE *fp )
{
  int mask[MAS_LENGTH] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF,
  0x3FF, 0x7FF, 0xFFF};
  if (buffer->bcount + nbits >= BITS_MAX){
    buffer->bits = buffer->bits << (BITS_MAX - buffer->bcount);
    
    int ctem = nbits + buffer->bcount - BITS_MAX;
    int tem;
    tem = code & mask[ctem]; //left-over element
    code = code >> (nbits + buffer->bcount - BITS_MAX);
    code = code | buffer->bits;
    fwrite(&code, 1, 1, fp);
    if (ctem >= BITS_MAX){
      code = tem >> (ctem - BITS_MAX);
      fwrite(&code, 1, 1, fp);
      buffer->bcount = ctem - BITS_MAX;
      buffer->bits = tem & mask[buffer->bcount];
    } else {
      buffer->bits = tem;
      buffer->bcount = ctem;
    }
  } else {
    buffer->bits = buffer->bits << nbits;
    buffer->bits |= code;
    buffer->bcount += nbits;
  }
}

/** If there are any bits buffered in buffer, write them out to the
    given file in the high-order bit positions of a byte, leaving zeros
    in the low-order bits.
    @param buffer pointer to storage for unwritten bits left over
    from a previous write.
    @param fp file these bits are to be written to, opened for writing
    in binary mode
*/
void flushBits( BitBuffer *buffer, FILE *fp )
{
  if (buffer->bcount != 0) {
    buffer->bits = buffer->bits << (BITS_MAX - buffer->bcount);
    fwrite(&(buffer->bits), 1, 1, fp);
  }
}

int getLength(int bin, int len)
{
  if (len == 1) {
    return -1;
  }
  int length = -1;
//   int tem = bin;
  while (len){
    if ((bin & 0x03) == 0){
      length = len;
    }
    bin = bin >> 1;
    len--;
  }
  return length;
}

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
int readBits (BitBuffer *buffer, FILE *fp )
{
  if (buffer->bcount > 1 && buffer->bits == 0) {
    return -1;
  }
  
  int len;
  int tem = buffer->bits;
  int mask[MAS_LENGTH] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0x1FF,
  0x3FF, 0x7FF, 0xFFF};

  if ((len = getLength(tem, buffer->bcount)) != -1) {
    buffer->bcount -= len;
    buffer->bits = tem & mask[buffer->bcount];
    return tem >> buffer->bcount;
  }

  if (feof(fp)) {
    if (buffer->bits != 0) {
      return -2;
    } else {
      return -1;
    }
  }
  int result = 0x00;
  
  while ((len = getLength(tem, buffer->bcount)) == -1 && (result = fgetc(fp)) != EOF) {
    if ( (result >> (BITS_MAX - 1)) == 0 && result != 0 && buffer->bcount == 0) {
      return -2;
    }
    tem = (tem << BITS_MAX) | result;
    buffer->bcount += BITS_MAX;
  }
  if (len == -1) {
    return -1;
  }
  buffer->bcount -= len;
  result = tem >> buffer->bcount;
  buffer->bits = tem & mask[buffer->bcount];
  return result;
}
