                                                 AUM SRI SAI RAM
Assignment model Algorithim Implementation
	This project titled "ASSIGNMENT MODEL" is a way to find 'the best person for the job'.
    The situation can be illustrated by the assignment of workers with varying degrees of skill to jobs.

Aim:
	The objectieve of the model is to determine the minimum-cost assignment of workers to jobs.

Process:
	This contains header, main, function, text & Make files.
	Header file contains the prototypes and the global variables.
	Main file contains the functions written in another file that are to be implemented.
	In function the algorithims are written to solve assignment problem.
	 void inputArray(int m,int n) - This function takes the input from the file in form of 2-D array.
	 void hungarian() - This function first finds the column minima from each column and subrtacts it from all the entries,then finds the optimal solution from the resulting matrix.
	 void doubleCheck(int row_dec[M],int col_inc[N],int col_mate[M],int cost) - This function gets the feasible matrix if the above function is not able to get the optimal assignment.
	 void finalSol(int cost) - This function gives us the final optimal matrix with zero entries as the feasible assignment in form of a table.

 
