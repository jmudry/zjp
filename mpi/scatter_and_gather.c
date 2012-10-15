#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


int main(int argc, char **argv)
{
	int np, rank;

	long int e;
	long int p = -1;
	int i;
	
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);	

	int vector[np];	
	int rnumber;
	if (rank == 0) {
		printf("Wylosowane liczby przez ROOT\n");
		for (i = 0; i < np; i++) {
			vector[i] =  (int)(rand() % 100);
			printf("%d :\t%d \n",i,vector[i]);
		} 
	}
		MPI_Scatter(vector, 1, MPI_INT, &rnumber, 1, MPI_INT, 0, MPI_COMM_WORLD); 

	printf("Proces numer %d otrzymał liczbe: %d\n", rank, rnumber);
	
		
	
	
	MPI_Finalize();
	return 0;
}
