/*                                               AUM SRI SAI RAM
Name:HEAM CHAND B & P S SRUJAN
Regd.no:173202, 171207
Dste:23-03-2020.
*/
//This file contains the  main functions that are defined in header file to solve 'LPP' problem using "SIMPLEX METHOD".
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
