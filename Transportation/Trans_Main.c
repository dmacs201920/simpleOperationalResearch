/*Purpose:
             Main program for the Transportation algorithm implementation
  Written on:
             20-03-2020
  Written by:
             P.Sai Srujan
             III BSc Maths
             171207
 */

#include"Trans_Header.h"

void main(int argc,char *args[]){
  node* head;  
  int s=0,d=0;
  /*
     Here,
          head is used as a header pointer to tableau constructed from the input data
          s, d are for taking input (ie. no.os sources and no. of destinations)
   */
  if(argc!=2){
    printf("Incorrect no. of args...\n");
    exit(0);
  }
  f=fopen(args[1],"a+");
  if(f==NULL){
    printf("Couldn't open the file...\n");
    exit(0);
  }
  
  fscanf(f,"%d",&s),fgetc(f),fscanf(f,"%d",&d),fgetc(f);

  head = constructTableu(s, d);
  fprintf(f,"\n\n");
  display(head);
  initialiseNW(head);
  printf("\n");
  display(head);
  printf("\n");
  iter_nFindSol(head);
  printf("\n");
}

