#include <stdio.h>

int main(int argc, char **argv){
	int size = 4;
	// matrix[wiersz][kolumna]	
	int matrix[size][size];
	int vector[size];
	int result[size];
	int i,j;
	
	for (i = 0; i < size; i++) {
		result[i] = 0;
	}
	
	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			matrix[i][j] = (int)(rand() % 10);	
		}
		vector[i] =  (int)(rand() % 10);	
	}

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			result[i] += matrix[i][j] * vector[j];
		}
	}

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			printf("%d\t",matrix[i][j]);
		}
		printf("| %d\t|", vector[i]);
		printf("| %d\t|\n", result[i]);
	}

	



}

