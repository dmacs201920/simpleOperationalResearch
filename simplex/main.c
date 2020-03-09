#include "header.h"

void main(int argc[],char *argv[])
{
	FILE *f;
	f = fopen(argv[1],"a");
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

