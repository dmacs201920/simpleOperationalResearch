# The Makefile contains the Assignment model problem files that are need to be compiled & executed.

Hungarian:	Assign_Func.o Assign_Main.o
	gcc -o  Hungarian Assign_Main.o Assign_Func.o -g

Assign_Main.o:	Assign_Main.c Assign_Header.h
	gcc -c -g Assign_Main.c

Assign_Func.o: Assign_Func.c Assign_Header.h
	gcc -c -g Assign_Func.c 

clean:
	rm -f *.s *.o *FinalExe
