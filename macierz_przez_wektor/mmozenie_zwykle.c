#include <stdio.h>
#include <time.h>
#define TIMER_SCALE  1000000000
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char **argv){
	int size = 1000;
	int count_loop = 1000;
	double sum_time = 0;
	long int start;
	double execution_time;
	// matrix[wiersz][kolumna]	
	int matrix[size][size];
	int vector[size];
	int result[size];
	int i,j,k;
	srand(time(0));
	for (i = 0; i < size; i++) {
		result[i] = 0;
	}
/*	
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			matrix[i][j] = (int)(rand() % 10);	
		}
		vector[i] =  (int)(rand() % 10);	
	}
*/
	for (k = 0; k < count_loop; k++){
		start = czas();
		for (i = 0; i < size; i++){
			for (j = 0; j < size; j++){
				result[i] += matrix[i][j] * vector[j];
			}
		}
		execution_time = (double)(czas() - start)/(double)TIMER_SCALE; 
	//	printf("Koniec obliczeń, czas obliczeń = %f\n", execution_time);
		sum_time += execution_time;
	}
	printf("Koniec obliczeń, czas obliczeń =%f %f\n", sum_time, sum_time/count_loop);

/*
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			printf("%d\t",matrix[i][j]);
		}
		printf("| %d\t|", vector[i]);
		printf("| %d\t|\n", result[i]);
	}
*/
	



}


