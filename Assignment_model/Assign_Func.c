#include "Assign_Header.h"

#define INF (0x7FFFFFFF)
#define verbose (1)

void inputArray(int m,int n)
{
  Array= malloc(m*sizeof(int));
  Result= malloc(m*sizeof(int));
  int i,j,data;
  for(i=0;i<m;i++){
    Array[i]=(int *) malloc(n*sizeof(int));
    Result[i]=(int *) malloc(n*sizeof(int));
  }
  for (i=0;i<m;++i)
    for (j=0;j<n;++j){
      fscanf(f,"%d",&data);
      fgetc(f);
      Array[i][j]=data;
    }
}

void hungarian(int m, int n)
{
  int i,j;
  int false=0,true=1;

  int k;
  int l;
  int s;
  int col_mate[m];
  int row_mate[n];
  int parent_row[n];
  int unchosen_row[m];
  int t;
  int q;
  int row_dec[m];
  int col_inc[n];
  int slack[n];
  int slack_row[n];
  int unmatched;
  int cost=0;

  for (i=0;i<m;++i)
    for (j=0;j<n;++j)
      Result[i][j]=false;

  // Begin subtract column minima in order to start with lots of zeroes 12
  printf("Using heuristic\n");
  for (l=0;l<n;l++)
  {
    s=Array[0][l];
    for (k=1;k<n;k++)
      if (Array[k][l]<s)
	s=Array[k][l];
    cost+=s;
    if (s!=0)
      for (k=0;k<n;k++)
	Array[k][l]-=s;
  }
  // End subtract column minima in order to start with lots of zeroes 12

  // Begin initial state 16
  t=0;
  for (l=0;l<n;l++)
  {
    row_mate[l]= -1;
    parent_row[l]= -1;
    col_inc[l]=0;
    slack[l]=INF;
  }
  for (k=0;k<m;k++)
  {
    s=Array[k][0];
    for (l=1;l<n;l++)
      if (Array[k][l]<s)
	s=Array[k][l];
    row_dec[k]=s;
    for (l=0;l<n;l++)
      if (s==Array[k][l] && row_mate[l]<0)
      {
	col_mate[k]=l;
	row_mate[l]=k;
	if (verbose)
	  printf("matching col %d==row %d\n",l,k);
	goto row_done;
      }
    col_mate[k]= -1;
    if (verbose)
      printf("node %d: unmatched row %d\n",t,k);
    unchosen_row[t++]=k;
row_done:
    ;
  }
  // End initial state 16

  // Begin Hungarian algorithm 18
  if (t==0)
    goto done;
  unmatched=t;
  while (1)
  {
    if (verbose)
      printf("Matched %d rows.\n",m-t);
    q=0;
    while (1)
    {
      while (q<t)
      {
	// Begin explore node q of the forest 19
	{
	  k=unchosen_row[q];
	  s=row_dec[k];
	  for (l=0;l<n;l++)
	    if (slack[l])
	    {
	      int del;
	      del=Array[k][l]-s+col_inc[l];
	      if (del<slack[l])
	      {
		if (del==0)
		{
		  if (row_mate[l]<0)
		    goto breakthru;
		  slack[l]=0;
		  parent_row[l]=k;
		  if (verbose)
		    printf("node %d: row %d==col %d--row %d\n",
			t,row_mate[l],l,k);
		  unchosen_row[t++]=row_mate[l];
		}
		else
		{
		  slack[l]=del;
		  slack_row[l]=k;
		}
	      }
	    }
	}
	// End explore node q of the forest 19
	q++;
      }

      // Begin introduce a new zero into the matrix 21
      s=INF;
      for (l=0;l<n;l++)
	if (slack[l] && slack[l]<s)
	  s=slack[l];
      for (q=0;q<t;q++)
	row_dec[unchosen_row[q]]+=s;
      for (l=0;l<n;l++)
	if (slack[l])
	{
	  slack[l]-=s;
	  if (slack[l]==0)
	  {
	    // Begin look at a new zero 22
	    k=slack_row[l];
	    if (verbose)
	      printf(
		  "Decreasing uncovered elements by %d produces zero at [%d,%d]\n",
		  s,k,l);
	    if (row_mate[l]<0)
	    {
	      for (j=l+1;j<n;j++)
		if (slack[j]==0)
		  col_inc[j]+=s;
	      goto breakthru;
	    }
	    else
	    {
	      parent_row[l]=k;
	      if (verbose)
		printf("node %d: row %d==col %d--row %d\n",t,row_mate[l],l,k);
	      unchosen_row[t++]=row_mate[l];
	    }
	    // End look at a new zero 22
	  }
	}
	else
	  col_inc[l]+=s;
      // End introduce a new zero into the matrix 21
    }
breakthru:
    // Begin update the matching 20
    if (verbose)
      printf("Breakthrough at node %d of %d!\n",q,t);
    while (1)
    {
      j=col_mate[k];
      col_mate[k]=l;
      row_mate[l]=k;
      if (verbose)
	printf("rematching col %d==row %d\n",l,k);
      if (j<0)
	break;
      k=parent_row[j];
      l=j;
    }
    // End update the matching 20
    if (--unmatched==0)
      goto done;
    // Begin get ready for another stage 17
    t=0;
    for (l=0;l<n;l++)
    {
      parent_row[l]= -1;
      slack[l]=INF;
    }
    for (k=0;k<m;k++)
      if (col_mate[k]<0)
      {
	if (verbose)
	  printf("node %d: unmatched row %d\n",t,k);
	unchosen_row[t++]=k;
      }
    // End get ready for another stage 17
  }
done:

  // Begin doublecheck the solution 23
  for (k=0;k<m;k++)
    for (l=0;l<n;l++)
      if (Array[k][l]<row_dec[k]-col_inc[l])
	exit(0);
  for (k=0;k<m;k++)
  {
    l=col_mate[k];
    if (l<0 || Array[k][l]!=row_dec[k]-col_inc[l])
      exit(0);
  }
  k=0;
  for (l=0;l<n;l++)
    if (col_inc[l])
      k++;
  if (k>m)
    exit(0);
  // End doublecheck the solution 23
  // End Hungarian algorithm 18

  for (i=0;i<m;++i)
  {
    Result[i][col_mate[i]]=true;
    /*TRACE("%d - %d\n", i, col_mate[i]);*/
  }
  for (k=0;k<m;++k)
  {
    for (l=0;l<n;++l)
    {
      /*TRACE("%d ",Array[k][l]-row_dec[k]+col_inc[l]);*/
      Array[k][l]=Array[k][l]-row_dec[k]+col_inc[l];
    }
    /*TRACE("\n");*/
  }
  for (i=0;i<m;i++)
    cost+=row_dec[i];
  for (i=0;i<n;i++)
    cost-=col_inc[i];
  printf("Cost is %d\n",cost);
}

