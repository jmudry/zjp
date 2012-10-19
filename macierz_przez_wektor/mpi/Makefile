MPICC  = mpicc
MPIRUN = mpirun
np=4
size=16

all: mnozenie

mnozenie: mnozenie.c
	$(MPICC) mnozenie.c -lrt -o mnozenie

run: mnozenie
	$(MPIRUN) -np $(np) ./mnozenie $(size)

clean: 
	rm -f mnozenie *.o *~ 
