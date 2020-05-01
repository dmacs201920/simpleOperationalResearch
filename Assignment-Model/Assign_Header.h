/*                                            AUM SRI SAI RAM                                         
Name:HEAM CHAND B.
Regd.no:173202.
Date of submission:20th-March,2020.
*/
//This is a header file that contains the prototypes & global varaibles are declared which are required to solve the Assignment problem using Hungarian method.

#include <stdio.h>
#include <stdlib.h>

static int **Array;
static int **Result;
FILE *f;

void inputArray(int m,int n);	//Takes the input from the file
void hungarian();	//Solves the assignment model using hungarian method
void finalSol(int cost);	//Gives the Optimal solution & Optimal assignment in form of a table
void doubleCheck(int row_dec[],int col_inc[],int col_mate[],int cost);	//Checks for the fesable solution
void nl(int k);		//Draws the lines at the end of the program
