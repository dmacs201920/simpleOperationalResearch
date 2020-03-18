# The Makefile

Out:	 Simplex_Main.o Simplex_Func.o
	gcc -o Out Simplex_Main.o Simplex_Func.o -g

Simplex_Main.o: Simplex_Main.c
	gcc -c Simplex_Main.c -g

Simplex_Func.o: Simplex_Func.c
	gcc -c Simplex_Func.c -g
clean:
	rm -f *.s *.o *Out
