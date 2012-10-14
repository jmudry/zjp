/**
 * Kompilacja:
 *  $ mpicc mpitest.c -o mpitest
 * Uruchomienie
 *  $ mpirun -np 4 ./mpitest
 * */

#include <stdio.h>
#include "mpi.h"
#include <time.h>
#define TIMER_SCALE  1000000000

long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char **argv)
{
	int np, rank;
	long int start;
	
	long int przedzial = 100000000;
	long int e;
	long int p = -1, i;
	
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	long int procesow = np;
	p = rank;
	long int vector[procesow+1];	
	
	long int global_suma = 0;
	long int suma = 0;
	
	start = czas();
	long int pocz;
	if (rank == 0) {
		for (i = 0, pocz = 0; i < procesow +1 ; i+=1) {
			vector[i] = pocz;
			pocz += przedzial/procesow;		
		}	
	} 
	MPI_Bcast( vector, procesow+1, MPI_LONG, 0,  MPI_COMM_WORLD);	
	
	for (i = vector[rank]; i < vector[rank+1]; i++) {
		suma += i;
	}
	printf("Koniec obliczeń, czas obliczeń = %f\n", (double)(czas() - start)/(double)TIMER_SCALE);	
	printf("Dla przedzialu <%ld,%ld) proces nr: %d obliczył:  %ld\n", vector[rank],vector[rank+1],rank, suma);
			
	suma = MPI_Reduce(&suma, &global_suma, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);	
		
	
	if (rank == 0) {
		printf("GLOBALNA SUMA to %ld\n", global_suma);
	} 

	//printf("Witaj, jestem \e[31m%d\e[0m z pośród \e[35m%d\e[0m procesów.\n", rank, np);
	MPI_Finalize();
	return 0;
}
