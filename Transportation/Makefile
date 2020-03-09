run:	Trans_Main.o Trans_Func.o
		gcc -o run -g Trans_Main.o Trans_Func.o
Trans_Main.o:	Trans_Main.c Trans_Header.h
		gcc -c -g Trans_Main.c Trans_Header.h
Trans_Func.o:	Trans_Func.c Trans_Header.h
		gcc -c -g Trans_Func.c Trans_Header.h
clean:	
		rm -f *.o *.s run

