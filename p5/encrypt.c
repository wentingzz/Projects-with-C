/** Helpful program to report the value in every byte of stdin, in binary. */

#include <stdio.h>
#include <stdlib.h>
#include "codes.h"
#include "bits.h"
#define ARGC 3

int main(int argc, char* argv[])
{
  if (argc != ARGC){
    fprintf(stderr, "usage: encrypt <infile> <outfile>\n");
    return 1;
  }
  
  FILE * input = fopen(argv[1], "r");
  FILE * out = fopen(argv[2], "wb");
  if (!input || !out) {
    perror("file.txt: No such file or directory");
    fclose(input);
    fclose(out);
    return -1;
  }
  
  unsigned int ch;
  int de;
  BitBuffer * bb = malloc(sizeof(BitBuffer));
  bb->bits = 0x00;
  bb->bcount = 0;
  while (1) {
    ch = fgetc(input);
    if (feof(input)) {
      flushBits( bb, out );
      break;
    }
    if ( (de = symToCode(ch)) == -1) {
      fprintf(stderr, "Invalid file\n");
      free(bb);
      fclose(input);
      fclose(out);
      return 1;
    }
    writeBits(de, bitsInCode(ch), bb, out);
  }
  free(bb);
  fclose(input);
  fclose(out);
}
