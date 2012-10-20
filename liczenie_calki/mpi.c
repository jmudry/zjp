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

double f(double x) {
	return  pow(M_E, -x*x);
}

	// Wolfram: (e^-(x^2))dx from -2 to 2 = 1,76416
double liczCalke(double a, double b, int n){	
	double suma =0;
	double h = (b-a)/n;
	int i;
	double x = a;
	suma -= (f(a) + f(b))/2;
	for (i=0 ; i<= n ; i++){
		x += h;			
		suma += f(x);
	}
	return suma*h;

}


int main(int argc, char **argv){	
	int i, t;
	double a = -2;
	double b = 2;
	int n = 4000000;
	double h = (b-a)/n;
	long int start;
	double execution_time;
	int np, rank;
	double local_a, local_b, local_integral;
	int local_n;
	double integral = 0;
	
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);	
	local_n = (int) n/np;
	if (argc > 1) {
		if (!sscanf(argv[1], "%d", &n)) {
			if (rank == ROOT) {		
		 		printf("Zły paramter! Musi być liczbą całkowitą\n");
			}		
		};
	}	
	local_a = (double) a+rank*local_n*h;
	local_b = (double) local_a+local_n*h;	
	if (rank == ROOT) {
		start = czas();
	}

	local_integral = liczCalke(local_a,local_b,local_n);	
	MPI_Reduce(&local_integral, &integral, 1, MPI_DOUBLE, MPI_SUM, ROOT, MPI_COMM_WORLD);	
	
	if (rank == 0) {
		printf("Dla %d obiegów metodą trapezową całka wynosi %f\n",n,integral);
		printf("Koniec obliczeń, czas obliczeń = %f\n", (double)(czas() - start)/(double)TIMER_SCALE);
	} 

	MPI_Finalize();

	return 0;
}
