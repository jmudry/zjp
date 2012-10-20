#include <stdio.h>
#include <time.h>
#include <math.h>
#define TIMER_SCALE  1000000000
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
	long int start;
	double execution_time;

	if (argc > 1) {
		sscanf(argv[1], "%d", &n);
	}	
		
	double suma;
	start = czas();
	printf("Całka = %f\n", liczCalke(a,b,n));
	printf("Koniec obliczeń, czas obliczeń = %f\n", (double)(czas() - start)/(double)TIMER_SCALE);
	

	return 0;
}
