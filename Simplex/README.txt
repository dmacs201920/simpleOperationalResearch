     							AUM SRI SAI RAM
Simplex method Algorithim Implementation
	This project, titled "SIMPLEX METHOD" solve the given LPP algebraically.
Aim:
	To find the Optimal solution for the given objectieve function subject to given constraints.
        (All constraints are of <= type).
Process:
	This contains header, functions, main, text & Make files.
	Header file contains the prototypes that are written in function file.
	Main file contains the functions written in another file that are to be implemented.
	In function the algorithims are written to solve the given LPP by simplex method.
	 void Data(int argc,char *argv[]) - This function take the input from user and writes in a file and takes the data in double array..
	 void Simplex() - This function calls the other functions into it until the desired result is not obtained.
	 void Pivot() - This function finds the pivot element and finds the entering and leaving variables.
	 void Formula() - This function using the pivot element gets us the new array/table.
	 void Optimize() - This function finds the optimal solution.
	 