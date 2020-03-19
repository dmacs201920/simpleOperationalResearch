#include "Assign_Header.h"

void main(int argc,char *args[])
{
  int y,x,i;
  int **Result;int **Array;
  int m=0,n=0;
  if(argc!=2){
    printf("Incorrect no. of args...\n");
    exit(0);
  }
  f=fopen(args[1],"a+");
  if(f==NULL){
    printf("Couldn't open the file...\n");
    exit(0);
  }

  fscanf(f,"%d",&m),fgetc(f),fscanf(f,"%d",&n),fgetc(f);

  inputArray(m,n);

  hungarian();

}
