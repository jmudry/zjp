#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


int main(int argc, char **argv)
{
	int np, rank;

	long int e;
	long int p = -1;
	int i,j,k;	
	int root = 0;
	int size = 12;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);	
	
	int podzial = (int)size/np;
	int vector[size][size];	
	int rnumber[size][podzial];

	if (rank == root) {
		printf("Wylosowane liczby przez ROOT\n");
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
			vector[i][j] =  (int)(rand() % 100);
			} 
		} 

		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
			printf("%d\t",vector[j][i]);
			} 
			printf("\n");
		} 
	}

	for (i = 0; i < 2; i++) {
			for (j = 0; j < size; j++) {
			rnumber[i][j] = -1;
			} 
	} 

	for (k =0; k< size; k++ ){
		MPI_Scatter(vector[k], podzial, MPI_INT, &rnumber[k], podzial, MPI_INT, root, MPI_COMM_WORLD); 
	}


	printf("Proces numer %d otrzymał:\n", rank);
	
		for (i = 0; i < podzial; i++) {
			for (j = 0; j < np*podzial; j++) {
				printf("%d\t",rnumber[j][i]);
			} 
			printf("\n");
		} 

	MPI_Finalize();
	return 0;
}
