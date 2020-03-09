/*Purpose:
  Written on:
  Written by:
 */

#include"header.h"

void main(int argc,char *args[])
{
    node* head=NULL;
    int s=0,d=0,x,*a;
    if(argc!=2){
	printf("Incorrect no. of args...\n");
	exit(0);
    }
    f=fopen(args[1],"r");
    if(f==NULL){
	printf("Couldn't open the file...\n");
	exit(0);
    }
    /*
    printf("\n\t\t\tASSGINMENT MODEL\n");
    printf("Please enter no.of people and no.of work in the format [s d]:\t");
    scanf("%d%d",&s,&d);
    */
    fscanf(f,"%d",&s),fgetc(f),fscanf(f,"%d",&d),fgetc(f);
    head=constructTableu(head,s,d);
    display(head); 
    findMin(head);
    solution(head,s,d,a);
}
