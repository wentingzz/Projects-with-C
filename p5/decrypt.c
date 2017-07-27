#include <stdio.h>
#include <stdlib.h>
#include "codes.h"
#include "bits.h"
#define ARGC 3

int main(int argc, char *argv[])
{
  if (argc != ARGC){
    fprintf(stderr, "usage: decrypt <infile> <outfile>\n");
    return 1;
  }
  
  FILE * input = fopen(argv[1], "rb");
  if (!input){
    fprintf(stderr, "%s: No such file or directory\n", argv[1]);
    return 1;
  }
  
  FILE * out = fopen(argv[2], "w");
  if (!out) {
    fprintf(stderr, "%s: No such file or directory\n", argv[2]);
    fclose(input);
    return 1;
  }
  
  int next;
  BitBuffer * bb = malloc(sizeof(BitBuffer));
  bb->bits = 0x00;
  bb->bcount = 0;
  while ((next = readBits(bb, input)) != -1) {
    if ( next == -2) {
      fprintf(stderr, "Invalid file\n");
      free(bb);
      fclose(input);
      fclose(out);
      fclose(fopen(argv[2], "w"));
      return 1;
    }
    
    fprintf(out, "%c", (char)codeToSym(next));
  }
  free(bb);
  fclose(input);
  fclose(out);
}
