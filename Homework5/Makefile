hw5: main.o mem.o
	gcc main.o mem.o

main.o : main.c mem.h
	gcc -c main.c -Wall

mem.o: mem.c mem.h
	gcc -c -Wall mem.c
