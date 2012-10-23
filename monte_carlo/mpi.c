/*
	Testowanie na czterech procesach jest bardziej wydajne niż generowanie punktów przez jeden proces 
	gdyż równie dobrze każdy może generować je dla siebie wyliczyć i zapomnieć o nich a musimy deklarować
	wielką tablicę.

	Dla 100 000 000 punktów otrzymano wynik średnio: 1.4 s 
	za to przy sekwencyjnym rozwiązaniu wynik było: 3.4 s
	Przy generowaniu punktów przez proces root na 4 procesach przy tych danych 
	program wysypuje sie ;) dla połowy mniej punktów osiąga czas: 3.4 czyli troche słabo...
*/


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
	long int n = 10000000;
	long int in_circle = 0;
	double execution_time;
	long int start;
	double pi,x,y;
  
	int i, rank,np; 
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);		
	srand(czas()+rank);
	printf("rank %d %d\n", rank, (int)rand());
	if (argc > 1) {
		if (!sscanf(argv[1], "%ld", &n)) {
			if (rank == ROOT) {		
		 		printf("Zły paramter! Musi być liczbą całkowitą\n");
			}		
		};
	}	

	long int local_in_circle = 0;
	long int local_n = (long int) n/np;		
	if (n % np != 0 && rank == ROOT) {
		printf("niepodzielne:\t %d ", (int)n % np);
		local_n += n % np;
	}

	if (rank == ROOT) {
		start = czas();
	}

	for (i = 0; i < local_n; i++) {           
  	x = ((double)rand() / (RAND_MAX))*2 - 1;
    y = ((double)rand() / (RAND_MAX))*2 - 1;
    if(x*x + y*y <= 1) {
    	local_in_circle++;
    }
  }

	MPI_Reduce(&local_in_circle, &in_circle, 1, MPI_LONG, MPI_SUM, ROOT, MPI_COMM_WORLD);	
	
	if (rank == ROOT) {
		pi = 	4 * (double)in_circle / n;
		execution_time = (double)(czas() - start)/(double)TIMER_SCALE;
		printf("Dla liczby punktów w kole: %ld \n", n);
		printf("Z math.h \tPI = %.40lf\n", M_PI);
		printf("Wyliczone\tPI = %.40lf\n", pi);
		printf("Czas obliczeń = %f\n", execution_time);
	}
	
	MPI_Finalize();
	return 0;
}
