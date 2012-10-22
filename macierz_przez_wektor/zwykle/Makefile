size=16

all: mnozenie

mnozenie: mnozenie.c
	$(MPICC) mnozenie.c -lrt -o mnozenie

run: mnozenie
	./mnozenie $(size)

clean: 
	rm -f mnozenie *.o *~ 
