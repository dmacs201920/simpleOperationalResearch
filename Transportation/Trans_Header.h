/*Purpose:
             To declare 
               1.Functions used.
               2.Non-primitive datatypes.
               3.Global variable.
  Written by:
             P.Sai Srujan
             III B.Sc-Maths
             171207
  Written on:
             
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
  int cost;
  int quantity;
  struct node *right, *down;
  int r, c;
  int basic;
  int coeff;
} node;

typedef struct clos_path{
  node *var;
  struct clos_path *next;
} clos_path;

typedef struct nonbasic{
  node *var;
  struct nonbasic *next;
} nonbasic;

FILE *f;
node* newNode(int d,int r,int c);
void display(node *head);
node* constructTableu(int m, int n);
nonbasic* addNonb(node *g,nonbasic *head);
void initialiseNW(node *head);
int enterQuan(node *n,int r, int c);
void iter_nFindSol(node *head);
int findNum(int a[],int i,int j);
node *findEnt(nonbasic *h);
void findLeav(clos_path *h,node *ent,node *head);
clos_path* addNodeCl(node *g,clos_path *head,int p);
clos_path* findNbrs(node **t,clos_path *h,int c);
clos_path* delNodeCl(node *h3,clos_path *h1);
void Initialise(int *A,int *B,int n);
int findNode(node *h,clos_path *h3);
void nl(int k);
void displayAns(node *head);
void BalanceTableau(int *array,int *M,int *N,node *head);
