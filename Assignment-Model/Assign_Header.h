/*                                               AUM SRI SAI RAM
Name:HEAM CHAND B.
Regd.no:173202.
Dste:23-03-2020.
*/
//This file is the header file to solve 'THE ASSIGNMENT MODEL' problem using "HUNGARIAN METHOD".

#include <stdio.h>
#include <stdlib.h>

static int **Array;                  
static int **Result;
FILE *f;

void inputArray(int m,int n);
void hungarian();
void finalSol(int cost);
void doubleCheck(int row_dec[],int col_inc[],int col_mate[],int cost);
void nl(int k);
