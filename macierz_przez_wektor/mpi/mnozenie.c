#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define TIMER_SCALE  1000000000
#define ROOT 0
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char **argv){	
	if (argc > 1) {
		int size;
		int np, rank;

		MPI_Status status;
		MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &np);	
		
		if (sscanf(argv[1], "%d", &size)) {
			if (size % np == 0) {
				long int start;
				double sum_execution_time = 0;
				int count_loop_main = 100;
				double execution_time;
			
				int podzial = (int)size/np;
				int matrix[size][size]; // [kolumna, wiersz]
				int vector[size];
				int result[size];
				int res_result[podzial];
				int i,j,k,l;
				int res_matrix[size][podzial]; // [kolumna, wiersz]
		
				for (l = 0; l < count_loop_main; l++) {
				
					srand(time(0));

					// inicjalizacja wektora rozwiązania
					for (i =0; i < podzial; i++) {
						res_result[i] = 0;
					}	
			
					// randomowe wartości
					if (rank == ROOT) {
						for (i = 0; i < size; i++){
							for (j = 0; j < size; j++){
								matrix[i][j] = (int)(rand() % 10);	
							}
							vector[i] =  (int)(rand() % 10);	
						}
					}

					start = czas();
					/* Wysłanie czśsci macierzy do procesów */
					for (k =0; k< size; k++ ){
						MPI_Scatter(matrix[k], podzial, MPI_INT, &res_matrix[k], podzial, MPI_INT, ROOT, MPI_COMM_WORLD); 
					}
					/* Wysłanie vektora do wszystkich */
					MPI_Bcast( vector, size, MPI_INT, 0,  MPI_COMM_WORLD);	
		
					//właściwe swojej części przez wektor
					for (i = 0; i < size; i++){
						for (j = 0; j < size; j++){
							res_result[i] += res_matrix[j][i] * vector[j];
						}
					}
				
					MPI_Gather(&res_result, podzial, MPI_INT, result, podzial, MPI_INT, ROOT, MPI_COMM_WORLD);	
					execution_time = (double)(czas() - start)/(double)TIMER_SCALE; 
					sum_execution_time += execution_time;
				
			
				} 
					if (rank == ROOT) {
						//wyświetlanie wyniku
						if (size <= 16) {
							for (i = 0; i < size; i++){
								for (j = 0; j < size; j++){
									printf("%d\t",matrix[j][i]);
								}
								printf("| %d\t|", vector[i]);
								printf("| %d\t|\n", result[i]);
							}
					//	printf("\nKoniec obliczeń, czas obliczeń = %f\n", execution_time);
					}
					printf("\nKoniec obliczeń, średni czas obliczeń = %f\n", (double)execution_time/count_loop_main);
				}
			} else {
				if (rank == ROOT) {	printf("Źle dobrane parametry wielkość macierzy musi być podzielna przez liczbe procesów.\n"); }
				}
		} else {
			if (rank == ROOT) { printf("Zly paramter wywoałania programu! Musi to być liczba.\n"); }
		}
	}	else {
		printf("Musisz podać dwa parametry: liczba procesów, rozmiar macierzy\n");
	}
	
	MPI_Finalize();
	
return 0;
}


