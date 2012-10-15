#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


int main(int argc, char **argv)
{
	int np, rank;

	long int e;
	long int p = -1;
	int i;	
	int root = 0;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);	

	int vector[np];	
	int rnumber;
	if (rank == root) {
		printf("Wylosowane liczby przez ROOT\n");
		for (i = 0; i < np; i++) {
			vector[i] =  (int)(rand() % 100);
			printf("%d :\t%d \n",i,vector[i]);
		} 
	}
		MPI_Scatter(vector, 1, MPI_INT, &rnumber, 1, MPI_INT, root, MPI_COMM_WORLD); 

	printf("Proces numer %d otrzymał liczbe: %d\n", rank, rnumber);
	rnumber = (int)(rand() % rnumber);
	printf("Proces numer %d otrzymał liczbe nową liczbe : %d\n", rank, rnumber);
	MPI_Gather(&rnumber, 1, MPI_INT, vector, 1, MPI_INT, root, MPI_COMM_WORLD);
	if (rank == root) {
	printf("Odebrane liczby przez ROOT\n");
		for (i = 0; i < np; i++) {
			printf("%d :\t%d \n",i,vector[i]);
		} 
	}
		
	MPI_Finalize();
	return 0;
}
