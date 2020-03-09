
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct node 
{
  int data;
  int coeff;
  struct node *right, *down;
} node;

typedef struct sol
{
	node *var;
	struct sol *next;
} sol;

FILE *f;
node* newNode(int d);
void display(node* head);
node* constructTableu(node *,int m, int n);
void findMin(node *h);
void no_of_Zeroes(node *h,int m,int n,int array[m+n]);
node* solution (node *h ,int m ,int n, int array[m+n]);
sol *addSol(node *g,sol *head);
int findCoeff(node *head,int r);

