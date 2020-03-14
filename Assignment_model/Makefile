# The Makefile

FinalExe:	Assign_Func.o Assign_Main.o
	gcc -o FinalExe Assign_Main.o Assign_Func.o -g

Assign_Main.o:	Assign_Main.c Assign_Header.h
	gcc -c -g Assign_Main.c Assign_Header.h 

Assign_Func.o: Assign_Func.c Assign_Header.h
	gcc -c -g Assign_Func.c Assign_Header.h

clean:
	rm -f *.s *.o *FinalExe
