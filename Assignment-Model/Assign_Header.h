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

