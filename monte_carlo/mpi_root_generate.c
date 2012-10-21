#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"
#define TIMER_SCALE  1000000000
#define ROOT 0
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char **argv){	
	long int n = 20000000;
	srand(time(0));
	long int in_circle = 0;
	double execution_time;
	long int start;
	double pi,x,y;
	int i, rank,np; 
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);	
	
	if (argc > 1) {
		if (!sscanf(argv[1], "%ld", &n)) {
			if (rank == ROOT) {		
		 		printf("Zły paramter! Musi być liczbą całkowitą\n");
			}		
		};
	}	
	 
	long int local_in_circle = 0;
	long int local_n = (long int) n/np;		

	double rand_numbers[n];
	if (rank == ROOT) {
		start = czas();
		for (i = 0; i < n; i++) {           
  		rand_numbers[i] = ((double)rand() / (RAND_MAX))*2 - 1;
  	}
	}
	double res_rand_numbers[(int) local_n];
	MPI_Scatter(rand_numbers, local_n, MPI_DOUBLE, &res_rand_numbers, local_n, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
	
	for (i = 0; i < local_n; i +=2) {           
    if(res_rand_numbers[i]*res_rand_numbers[i] + res_rand_numbers[i+1]*res_rand_numbers[i+1] <= 1) {
    	local_in_circle++;
    }
  }

	MPI_Reduce(&local_in_circle, &in_circle, 1, MPI_LONG, MPI_SUM, ROOT, MPI_COMM_WORLD);	
	
	if (rank == ROOT) {
		pi = 	4 * (double)in_circle / n*2;
		execution_time = (double)(czas() - start)/(double)TIMER_SCALE;
		printf("Dla liczby punktów w kole: %ld \n", n);
		printf("Z math.h \tPI = %.40lf\n", M_PI);
		printf("Wyliczone\tPI = %.40lf\n", pi);
		printf("Czas obliczeń = %f\n", execution_time);
	}
	
	MPI_Finalize();
	return 0;
}
