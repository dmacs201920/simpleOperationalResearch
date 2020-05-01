/*                                            AUM SRI SAI RAM                                         
Name:HEAM CHAND B.
Regd.no:173202.
Date of submission:20th-March,2020.
*/
//This file contains the functions of the prototypes that are decleared in the header file which are required to solve the Assignment problem using Hungarian method.

#include "Assign_Header.h"              //Including self created header file
#define INF (0x7FFFFFFF)                //Defines INF in form of Hexadecimal number
//#define verbose (1)                     //Defines verbose (1) as a true statement in the while condition

int M,N;                        //Decleared as global variables of type integer

//This function takes the input from the file as defined and stores the data in form of 2-D array
void inputArray(int m,int n)
{
    Array= malloc(m*sizeof(int));           //Using dynamic allocation to take no.of rows in 2-D array Array 
    Result= malloc(m*sizeof(int));          //Using dynamic allocation to take no.of rows in 2-D the array Result
    int i,j,data;
    for(i=0;i<m;i++)
    {
        Array[i]=(int *) malloc(n*sizeof(int));         //Using dynamic allocation to take the no.of column in 2-D array Array
        Result[i]=(int *) malloc(n*sizeof(int));        //Using dynamic allocation to take the no.of column in 2-D the array Result
    }
    M=m,N=n;
    for (i=0;i<M;++i)
        for (j=0;j<N;++j)
        {
            fscanf(f,"%d",&data);                   //Takes input from the text file
            fgetc(f);
            Array[i][j]=data;
        }
}

//This function runs the processes of the hungarian method
void hungarian()
{
    //Temporary variables & 1-D arrays of type int are decleared
    int i,j;

    unsigned int m=M,n=N;
    int k;
    int L;
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
        for (j=0;j<N;++j)                   //This loop initialises entries in array Result to 0
            Result[i][j]=0;                                         
    // Begin subtract column minimum in order to start with zeroes
    for (L=0;L<n;L++)
    {
        s=Array[0][L];
        for (k=1;k<n;k++)
            if (Array[k][L]<s)                      //Checks for the miinmum entries for each column in the matrix
                s=Array[k][L];
        cost+=s;                        //Adds all the minimum entries in each column of the matrix
        if (s!=0)
            for (k=0;k<n;k++)
                Array[k][L]-=s;
    }
    // End subtract column minimum in order to start with zeroes

    // Begin initial state of the hungarian algorithim 
    t=0;
    for (L=0;L<n;L++)
    {
        row_mate[L]= -1;                //Intitializes array to -1
        parent_row[L]= -1;              //Intitializes array to -1
        col_inc[L]=0;                   //Intitializes array to 0
        slack[L]=INF;
    }
    for (k=0;k<m;k++)
    {
        s=Array[k][0];
        for (L=1;L<n;L++)
            if (Array[k][L]<s)
                s=Array[k][L];
        row_dec[k]=s;                               //Stores the minimun of the row in an array
        for (L=0;L<n;L++)
            if (s==Array[k][L] && row_mate[L]<0)
            {
                col_mate[k]=L;
                row_mate[L]=k;
                break;
            }
        if(L==n)
        {
            col_mate[k]= -1;
            unchosen_row[t++]=k;
        }
    }
    // End initial state of the hungrain algorithim

    // Begin Hungarian algorithm 
    if (t==0)
        doubleCheck(row_dec,col_inc,col_mate,cost);             // Calls the function 'doubleCheck'
    unmatched=t;
    while (1)
    {
        q=0;
        while (1)
        {
            while (q<t)
            {
                // Begin explore's array to get the optimal solution
                {
                    k=unchosen_row[q];
                    s=row_dec[k];
                    for (L=0;L<n;L++)
                        if (slack[L])
                        {
                            int del;
                            del=Array[k][L]-s+col_inc[L];
                            if (del<slack[L])
                            {
                                if (del==0)
                                {
                                    if (row_mate[L]<0)
                                        goto breakthru;
                                    slack[L]=0;
                                    parent_row[L]=k;
                                    unchosen_row[t++]=row_mate[L];
                                }
                                else
                                {
                                    slack[L]=del;
                                    slack_row[L]=k;
                                }
                            }
                        }
                }
                // End's exploring the array for optimal solution
                q++;
            }

            // Begin introduce a new zero into the matrix 
            s=INF;
            for (L=0;L<n;L++)
                if (slack[L] && slack[L]<s)
                    s=slack[L];
            for (q=0;q<t;q++)
                row_dec[unchosen_row[q]]+=s;
            for (L=0;L<n;L++)
                if (slack[L])
                {
                    slack[L]-=s;
                    if (slack[L]==0)
                    {
                        // Begin looking at a new zero introduced into the matrix
                        k=slack_row[L];
                        if (row_mate[L]<0)
                        {
                            for (j=L+1;j<n;j++)
                                if (slack[j]==0)
                                    col_inc[j]+=s;
                            goto breakthru;
                        }
                        else
                        {
                            parent_row[L]=k;
                            unchosen_row[t++]=row_mate[L];
                        }
                        // End's looking at a new zero ehich is introduced into the matrix 
                    }
                }
                else
                    col_inc[L]+=s;
            // End's introducing a new zero into the matrix 
        }
breakthru:
        // Begin update the matching for fesable solution 
        while (1)
        {
            j=col_mate[k];
            col_mate[k]=L;
            row_mate[L]=k;
            if (j<0)
                break;
            k=parent_row[j];
            L=j;
        }
        // End updating the match for a fesable solution
        if (--unmatched==0)
            doubleCheck(row_dec,col_inc,col_mate,cost);
        // Begin to get ready for another stage if fesable solution can't be obtained
        t=0;
        for (L=0;L<n;L++)
        {
            parent_row[L]= -1;
            slack[L]=INF;
        }
        for (k=0;k<m;k++)
            if (col_mate[k]<0)
            {
                unchosen_row[t++]=k;
            }
        // End another stage if fesable solution is not obtained
    }

    doubleCheck(row_dec,col_inc,col_mate,cost);

}

//This function checks the matrix for the Optimal assignment
void doubleCheck(int row_dec[M],int col_inc[N],int col_mate[M],int cost)
{
    int k=0,L=0,i=0;
    // Begin doublecheck the solution for optimal solution
    for (k=0;k<M;k++)
        for (L=0;L<N;L++)
            if (Array[k][L]<row_dec[k]-col_inc[L])
                exit(0);
    for (k=0;k<M;k++)
    {
        L=col_mate[k];
        if (L<0 || Array[k][L]!=row_dec[k]-col_inc[L])
            exit(0);
    }
    k=0;
    for (L=0;L<N;L++)
        if (col_inc[L])
            k++;
    if (k>M)
        exit(0);
    // End doublecheck the solution for optimal solution
    // End Hungarian algorithm 
    
    //Begin to get the Optimal cost/solution
    for (i=0;i<M;++i)
    {
        Result[i][col_mate[i]]=1;
    }
    for (k=0;k<M;++k)
    {
        for (L=0;L<N;++L)
        {
            Array[k][L]=Array[k][L]-row_dec[k]+col_inc[L];
        }
    }
    for (i=0;i<M;i++)
        cost+=row_dec[i];
    for (i=0;i<N;i++)
        cost-=col_inc[i];
    //End to get the Optimal cost/solution
    finalSol(cost);
    exit(1);
}

//This function gives us the Optimal solution and Optimal assignment 
//in form of a tableu (that gives us the assignment of work for different people based on the position of zero entries in tableu).
void finalSol(int cost)
{
    char ch='A',sp=' ';
    int s=1,i,j;
    putchar('\n');
    printf("\nFinal Solution\n");
    putchar('\n');
    nl(100);
    printf("%6c",sp);
    for(j=0;j<N;j++)
        printf("|%3d  ", s++);
    putchar('\n');
    nl(40);
    for(i=0;i<M;i++) 
    {
        printf("|%3c  ", ch++);
        for(j=0;j<N;j++) 
        {
            if(Result==NULL) 
                break;
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

    printf("Optimal Cost is %d\n",cost);
    nl(100);
    for(i=0;i<M;i++){
        free(Result[i]);                //Frees the extra storage
        free(Array[i]);                 //Frees the extra storage
    }
    free(*Result);
    free(*Array);
}

//This function prints the line ---------------------------
void nl(int k)
{   
    int j; 
    for(j=0;j<k;j++) 
        putchar('-');                  //Loop to draw the line 
    putchar('\n'); 
}

