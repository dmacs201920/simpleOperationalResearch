/*Purpose:
  Written on:
  Written by:
 */

#include"Trans_Header.h"

void main(int argc,char *args[]){
  node* head;  
  int s=0,d=0;
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
  //display(head,"Final_Tableau");
}

