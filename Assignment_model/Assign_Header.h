#include <stdio.h>
#include <stdlib.h>

static int **Result, **Array;
FILE *f;

void inputArray();
void hungarian(int m, int n);
