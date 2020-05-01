/*                                            AUM SRI SAI RAM                                         
Name:HEAM CHAND B.
Regd.no:173202.
Date of submission:20th-March,2020.
 */
//This file contains the main function required to solve the Assignment problem using Hungarian method.

#include "Assign_Header.h"              //Including self created header file

//Begin the main function
void main(int argc,char *args[])
{
    int y,x,i;
    int **Result;int **Array;
    int m=0,n=0;
    if(argc!=2)
        //Checks wether the file is taken on command line or not
    {
        printf("Incorrect no. of args...\n");
        exit(0);
    }
    f=fopen(args[1],"a+");
    if(f==NULL)
        //Checks wether the file is empty or not
    {
        printf("Couldn't open the file...\n");
        exit(0);
    }
    //Here the input is taken as " m n " from file
    fscanf(f,"%d",&m);          //Takes input from the file as no.of row
    fgetc(f);
    fscanf(f,"%d",&n);          //Takes input from the file as no.of column
    fgetc(f);

    //Goes to input array to take theinput from file
    inputArray(m,n);

    //Goes into the hungarian function for solving the Assignment model problem
    hungarian();
    //Ends the main function
}
//Ends the main function
