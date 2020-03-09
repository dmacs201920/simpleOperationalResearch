/*                                     AUM SRI SAI RAM
Name:Heam Chand.
Regd.no:173202
 */

#include "header.h"

node* newNode(int d) 
{
    node* temp;
    temp=(node *) malloc(sizeof(node));
    temp->data=d;
    temp->coeff=1;
    temp->right=temp->down=NULL;
    return temp;
}

void display(node* head) 
{
    node *rp, *dp=head;
    while (dp) 
    {
	rp=dp;
	while (rp) 
	{
	    printf("%3d   ",rp->data);
	    rp=rp->right;
	}
	printf("\n");
	dp=dp->down;
    }
}

node* constructTableu(node *h,int m, int n) 
{
    int data;
    node *t=h,*t1=h;
    node* mainhead=NULL;
    node* head[m];
    node *righttemp, *newptr;

    for (int i = 0;i < m;i++) 
    {
	head[i]=NULL;
	for (int j=0;j < n;j++) 
	{   
	    /* 
	       printf("Please enter the cost given by the person-%d for a particular work in $-%d:\t",i+1,j+1);
	       scanf("%d",&data);
	     */	
	    fscanf(f,"%d",&data);fgetc(f);

	    newptr=newNode(data);
	    if (!mainhead)
		mainhead=newptr;
	    if (!head[i])
		head[i]=newptr;
	    else
		righttemp->right=newptr;
	    righttemp=newptr;
	} 
    }
    for (int i=0;i < m-1;i++) 
    {
	node *temp1=head[i], *temp2=head[i+1];
	while (temp1 && temp2) 
	{
	    temp1->down=temp2;

	    temp1=temp1->right;
	    temp2=temp2->right;
	}
    }
    return mainhead;
}

void findMin(node *h)
{
    int min,i=1,j=1;
    node *head=h,*t;
    while (head)
    {       t=head;
	min=head->data;
	head=head->right;
	while (head)
	{
	    if (head->data < min)
	    	min=head->data;min=min+0;
	    printf("$=%d\t\t\t",min=min+0);
	    head=head->right;
	}
	printf("\nminimum in a row %d = %d\t",i++,min);
	head=t;
	while (head)
	    head->data=head->data-min,head=head->right;
	head=t->down;
    }
    puts(" ");
    puts("Matrix after subtracting minimum form their respectieve row\n");
    display (h);
    puts(" ");

    head=h;
    while (head)
    {
	t=head;
	min=head->data;
	head=head->down;
	while (head)
	{
	    if (head->data <min)
		min=head->data;
	    head=head->down;
	}
	printf("\nminimum in a column %d = %d\t",j++,min);
	head=t;
	while (head)
	{
	    head->data=head->data-min;
	    head=head->down;
	}
	head=t->right;
    } 
    puts(" ");
    puts("Matrix after subtracting minimum form their respectieve column\n");
    display (h);

}

void no_of_Zeroes (node *h ,int m,int n,int array[m+n])
{
    puts("\nNo.of zero's in each row & columnn\n ");
    int zero=0,i=0,j=0,l=0;
    node *t=h,*head=t;
    while (head)
    {	
	while (head)
	{
	    if (head->data==0)
		zero++;
	    head=head->right;
	}
	printf("No.of zero's in row %d = %d\n",++l,zero);
	array[i++]=zero;
	zero=0;
	t=t->down;
	head=t;
    }
    j=m;
    zero=0;
    t=h;
    head=t;
    int k=0;
    while (head)
    {	
	while (head)
	{
	    if (head->data==0)
		zero++;
	    head=head->down;
	}
	printf("No.of zero's in column %d = %d\n",++k,zero);
	array[j++]=zero;
	zero=0;
	t=t->right;
	head=t;
    }
   printf("REACHED...\n"); 
    for(i=0;i<m+n;i++)
	printf("%d\t",array[i]);
}

node *solution (node *h ,int m ,int n,int array[m+n])
{
    no_of_Zeroes(h,m,n,array);
    node *t=h,*head=t,*t1;
    sol *h1;
    int i=0;
    while (head)
    {
	t=head,t1=t;
	if(array[i]==1){
	    if(findCoeff(head,1)==1)
		while(head->data!=0)
		    head=head->right;
	    if(head->coeff==1)
	    {
		h1=addSol(head,h1);
		while(t1)
		    t1->coeff=0,t1=t1->right;
		t1=t;
		t1=t1->down;
		while(t1)
		    t1->coeff=0,t1=t1->down;
	    }
	}
	head=head->down;
    }
    head=h;
    while (head)
    {
	t=head,t1=t;
	if(array[i]==1){
	    if(findCoeff(head,1)==1)
		while(head->data!=0)
		    head=head->down;
	    if(head->coeff==1)
	    {
		h1=addSol(head,h1);
		while(t1)
		    t1->coeff=0,t1=t1->right;
		t1=t;
		t1=t1->down;
		while(t1)
		    t1->coeff=0,t1=t1->down;
	    }
	}
	head=head->down;
    }
}

int findCoeff(node *head,int r)
{
    node *t=head;
    while(t){
	if(head->coeff==1)
	    return 1;
	t= r==1 ? t->right : t->down;
    }
}

sol *addSol(node *g,sol *head)
{
    sol *temp=head, *t=NULL;
    t=(sol *) malloc(sizeof(sol));
    t->var=g,t->next=NULL;
    if(temp==NULL) return t;
    while(temp->next!=NULL)
	temp=temp->next;
    temp->next=t;
    return head;
}

