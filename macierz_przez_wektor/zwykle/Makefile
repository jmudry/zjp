all: mnozenie

mnozenie: mnozenie.o
	cc mnozenie.o -lrt -o mnozenie

mnozenie.o: mnozenie.c
	cc -c mnozenie.c

run: mnozenie
	./mnozenie

clean: 
	rm -f mnozenie *.o
