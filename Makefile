
all: main

main: lib.o main.o
	cc main.o lib.o -o main

main.o: main.c
	cc -c main.c

lib.o: lib.c
	cc -c lib.c	

run: main
	./main

clean: 
	rm -f main *.o
