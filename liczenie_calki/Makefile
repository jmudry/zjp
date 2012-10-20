MPICC  = mpicc
MPIRUN = mpirun
np=4
size=400

all: zwykle mpi

zwykle: zwykle.c
	gcc zwykle.c -lrt -lm -o zwykle

mpi: mpi.c
	$(MPICC) mpi.c -lrt -lm -o mpi

run: mpi
	$(MPIRUN) -np $(np) ./mpi $(size)

run_zwykle: zwykle
	 ./zwykle $(size)

clean: 
	rm -f zwykle mpi *.o *~ 
