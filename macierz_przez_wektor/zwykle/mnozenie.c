/*
Przy rozwiązaniu mpi przy 4 procesach uzyskujemy średni czas 0.014
przy rozwiazaniu sekwencyjnym: 0.004
Widać dużą stratą czasu na komunikacji....
*/

#include <stdio.h>
#include <time.h>
#define TIMER_SCALE  1000000000
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char **argv){	
	if (argc > 1) {
		int size;
		if (sscanf(argv[1], "%d", &size)) {
			printf("Licze  dla rozmiaru: %d\n", size);
			long int start;
			double execution_time;
			int matrix[size][size];// [wiersz][kolumna]	
			int vector[size];
			int result[size];
			int i,j,k;
		
			srand(time(0));

			// inicjalizacja wektora rozwiązania
			for (i = 0; i < size; i++) {
				result[i] = 0;
			}

			// randomowe wartości
			for (i = 0; i < size; i++){
				for (j = 0; j < size; j++){
					matrix[i][j] = (int)(rand() % 10);	
				}
				vector[i] =  (int)(rand() % 10);	
			}

			//właściwe mnożenie macierzy przez wektor
				start = czas();
				for (i = 0; i < size; i++){
					for (j = 0; j < size; j++){
						result[i] += matrix[i][j] * vector[j];
					}
				}
				execution_time = (double)(czas() - start)/(double)TIMER_SCALE; 
				printf("Koniec obliczeń, czas obliczeń = %f\n", execution_time);

			//wyświetlanie wyniku
			if (size <= 16) {
				for (i = 0; i < size; i++){
					for (j = 0; j < size; j++){
						printf("%d\t",matrix[i][j]);
					}
					printf("| %d\t|", vector[i]);
					printf("| %d\t|\n", result[i]);
				}
			}
		} else {
			printf("Zly paramter wywoałania programu! Musi to być liczba.\n");
		}
	}	else {
		printf("Musisz podać dwa parametry: liczba procesów, rozmiar macierzy\n");
	}
	

	

return 0;

}


