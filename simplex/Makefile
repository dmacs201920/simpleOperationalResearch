# The Makefile

Out:	 main.o max-min_temp.o
	gcc -o Out main.o max-min_temp.o -g
main.o: main.c header.h
	gcc -c main.c -g
max-min_temp.o: max-min_temp.c header.h
	gcc -c max-min_temp.c -g
clean:
	rm -f *.s *.o *Out
