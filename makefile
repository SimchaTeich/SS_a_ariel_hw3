all: libex3.a main.o
	gcc -o stringProg main.o ex3.a -lcurses

libex3.a: ex3.o
	ar -rcs ex3.a ex3.o

ex3.o: ex3.c EX3.h
	gcc -c ex3.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o *.a stringProg

.PHONY: all clean