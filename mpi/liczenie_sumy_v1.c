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
	long int procesow = 4;
	long int przedzial = 100000000;
	long int e;
	long int p = -1, i;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	
	//printf("Start %d z %d\n", rank, np);
	p = rank;	
	
	//printf("Start t=%ld\n",start = czas());
	start = czas();
	if (rank == 0) {
		long int suma = 0;
		for (i = p*przedzial/procesow;i < (p+1)*przedzial/procesow; i++) {
			suma += i;
		}
		printf("Dla przedzialu <%ld,%ld) suma wynosi %ld\n", p*przedzial/procesow,(p+1)*przedzial/procesow, suma);
		int j =0;
		long int rec_suma = 0;
		for (j = 0; j<procesow -1 ; j++) {
			MPI_Recv(&rec_suma, 1, MPI_LONG, MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			suma += rec_suma;
			printf("suma otrzymana to %ld\n", rec_suma);	
		}	
		
		printf("GLOBALNA SUMA to %ld\n", suma);
	} else {
		long int suma = 0;
		for (i = p*przedzial/procesow;i < (p+1)*przedzial/procesow; i++) {
			suma += i;
		}
		printf("Koniec obliczeń, czas obliczeń = %f\n", (double)(czas() - start)/(double)TIMER_SCALE);
		printf("Dla przedzialu <%ld,%ld) suma wynosi %ld\n", p*przedzial/procesow,(p+1)*przedzial/procesow, suma);
		
		MPI_Send(&suma, 1, MPI_LONG, 0, 1234, MPI_COMM_WORLD);
	}

	//printf("Witaj, jestem \e[31m%d\e[0m z pośród \e[35m%d\e[0m procesów.\n", rank, np);
	MPI_Finalize();
	return 0;
}
