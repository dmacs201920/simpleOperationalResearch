#include "Simplex_Header.h"

void main(int argc[],char *argv[])
{
  system("clear");
  FILE *f;
  f = fopen(argv[1],"a+");
  if (f == NULL)
  { 
    printf("file doesn't exist\n");
    exit(-1);
  }
  Data();
  Simplex();
  Results();
  fclose (f);
}

