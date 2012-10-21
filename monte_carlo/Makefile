MPICC  = mpicc
MPIRUN = mpirun
np=4
size=1000000

all: zwykle mpi mpi_root_generate

zwykle: zwykle.c
	gcc zwykle.c -lrt -lm -o zwykle

mpi: mpi.c
	$(MPICC) mpi.c -lrt -lm -o mpi

mpi_root_generate: mpi_root_generate.c
	$(MPICC) mpi_root_generate.c -lrt -lm -o mpi_root_generate 

run: mpi
	$(MPIRUN) -np $(np) ./mpi $(size)

run_root: mpi_root_generate
	$(MPIRUN) -np $(np) ./mpi_root_generate $(size)

run_zwykle: zwykle
	 ./zwykle $(size)

clean: 
	rm -f zwykle mpi_root_generate mpi *.o *~ 
