#include <omp.h>
#include <unistd.h>
#include <stdio.h>
#include "time.h"
#include <stdlib.h>
#define TIMER_SCALE  1000000000

long int czas() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC, &t);
        return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}


// cc first.c -fopenmp
int main(){
		int i;
		int count = 100000; 
		float vector[count];
		int rand_max=65555;
		float max_el =-rand_max;		
		float scale=rand_max+1;		
		long int start;
		double suma = 0;
		float rand_number;
		
		srand(time(0));
		start = czas();
#pragma omp parallel for private(rand_number) reduction(+:suma)
		for (i = 0; i < count; i++) {
				rand_number = (float)rand() / (float)RAND_MAX*10;
				suma += rand_number;				
				//printf("vector[%d] = %f\n",i, vector[i]);
		}

		printf("Policzylem w %fs\n", (double)(czas() - start)/(double)TIMER_SCALE);
		printf("Suma = %f\n", suma);

	return 0;
}
