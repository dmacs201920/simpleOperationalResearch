#include "Assign_Header.h"
void main(int argc,char *args[])
{
    int y,x,i;
    int m=0,n=0;
    if(argc!=2)
    {
	printf("Incorrect no. of args...\n");
	exit(0);
    }
    f=fopen(args[1],"a+");
    if(f==NULL)
    {
	printf("Couldn't open the file...\n");
	exit(0);
    }
    fscanf(f,"%d",&m);
    fgetc(f);
    fscanf(f,"%d",&n);
    fgetc(f);

    inputArray(m,n);   
    hungarian(m,n);
    
    for (y=0;y<m;++y)
	for (x=0;x<n;++x)
	    if (Result[y][x])
		printf("%d and %d are connected in the assignment\n",y,x);
}
