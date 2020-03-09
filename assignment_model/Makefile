# The Makefile

FinalExe:	func.o main.o
	gcc -o FinalExe main.o func.o -g

main.o:	main.c header.h
	gcc -c -g main.c 

func.o: func.c header.h
	gcc -c -g func.c

clean:
	rm -f *.s *.o *FinalExe
