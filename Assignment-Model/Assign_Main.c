/*                                              AUM SRI SAI RAM
Name:HEAM CHAND B.
Regd.no:173202.
Date:23-03-2020.
*/
//This file contains the main function required to solve 'THE ASSIGNMENT MODEL' using "HUNGARIAN METHOD".
#include "Assign_Header.h"                    //This statement calls the header file in which prototypes are decleared.

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

  fscanf(f,"%d",&m);              //Reads the data from the file and assigns the no of rows.
  fgetc(f);
  fscanf(f,"%d",&n);              //Reads the data from the file and assigns the no of columns.
  fgetc(f);
  inputArray(m,n);                 //calls the function
  hungarian();                      //calls the function
}
