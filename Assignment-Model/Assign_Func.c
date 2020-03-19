#include "Assign_Header.h"
#define INF (0x7FFFFFFF)

#define verbose (1)

int M,N;

void inputArray(int m,int n)
{
    Array= malloc(m*sizeof(int));
    Result= malloc(m*sizeof(int));
    int i,j,data;
    for(i=0;i<m;i++)
    {
        Array[i]=(int *) malloc(n*sizeof(int));
        Result[i]=(int *) malloc(n*sizeof(int));
    }
    M=m,N=n;
    for (i=0;i<M;++i)
        for (j=0;j<N;++j)
        {
            fscanf(f,"%d",&data);
            fgetc(f);
            Array[i][j]=data;
        }
}

void hungarian()
{
    int i,j;

    unsigned int m=M,n=N;
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

    for (i=0;i<M;++i)
        for (j=0;j<N;++j)
        {
            Result[i][j]=0;
        }

    // Begin subtract column minima in order to start with lots of zeroes
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
    // End subtract column minima in order to start with lots of zeroes

    // Begin initial state
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
                break;
            }
        if(l==n)
        {
            col_mate[k]= -1;
            unchosen_row[t++]=k;
        }
    }
    // End initial state 

    // Begin Hungarian algorithm 
    if (t==0)
        doubleCheck(row_dec,col_inc,col_mate,cost);
    unmatched=t;
    while (1)
    {
        q=0;
        while (1)
        {
            while (q<t)
            {
                // Begin explore array
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
                // End explore array
                q++;
            }

            // Begin introduce a new zero into the matrix 
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
                        // Begin look at a new zero 
                        k=slack_row[l];
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
                            unchosen_row[t++]=row_mate[l];
                        }
                        // End look at a new zero 
                    }
                }
                else
                    col_inc[l]+=s;
            // End introduce a new zero into the matrix 
        }
breakthru:
        // Begin update the matching 
        while (1)
        {
            j=col_mate[k];
            col_mate[k]=l;
            row_mate[l]=k;
            if (j<0)
                break;
            k=parent_row[j];
            l=j;
        }
        // End update the matching 
        if (--unmatched==0)
            doubleCheck(row_dec,col_inc,col_mate,cost);
        // Begin get ready for another stage 
        t=0;
        for (l=0;l<n;l++)
        {
            parent_row[l]= -1;
            slack[l]=INF;
        }
        for (k=0;k<m;k++)
            if (col_mate[k]<0)
            {
                unchosen_row[t++]=k;
            }
        // End get ready for another stage 
    }

    doubleCheck(row_dec,col_inc,col_mate,cost);

}

void doubleCheck(int row_dec[M],int col_inc[N],int col_mate[M],int cost)
{
    int k=0,l=0,i=0;
    // Begin doublecheck the solution 
    for (k=0;k<M;k++)
        for (l=0;l<N;l++)
            if (Array[k][l]<row_dec[k]-col_inc[l])
                exit(0);
    for (k=0;k<M;k++)
    {
        l=col_mate[k];
        if (l<0 || Array[k][l]!=row_dec[k]-col_inc[l])
            exit(0);
    }
    k=0;
    for (l=0;l<N;l++)
        if (col_inc[l])
            k++;
    if (k>M)
        exit(0);
    // End doublecheck the solution 
    // End Hungarian algorithm 

    for (i=0;i<M;++i)
    {
        Result[i][col_mate[i]]=1;
    }
    for (k=0;k<M;++k)
    {
        for (l=0;l<N;++l)
        {
            Array[k][l]=Array[k][l]-row_dec[k]+col_inc[l];
        }
    }
    for (i=0;i<M;i++)
        cost+=row_dec[i];
    for (i=0;i<N;i++)
        cost-=col_inc[i];
    finalSol(cost);
    exit(1);
}

void finalSol(int cost)
{
    char ch='A',sp=' ';
    int s=1,i,j;
    putchar('\n');

    printf("\nFinal Solution\n");
    putchar('\n');
    printf("%6c",sp);
    for(j=0;j<N;j++)
    {
        printf("|%3d  ", s++);
    }
    putchar('\n');
    for(i=0;i<M;i++) 
    {
        printf("|%3c  ", ch++);
        for(j=0;j<N;j++) 
        {
            if(Result==NULL) break;
            if(Result[i][j]==1)
            {
                printf("|  0  ");
            }
            else
            {
                printf("|  -  ");
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Cost is %d\n",cost);

    for(i=0;i<M;i++){
        free(Result[i]);
        free(Array[i]);
    }
    free(*Result);
    free(*Array);
}
