#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define TIMER_SCALE  1000000000
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char **argv){	
	long int n = 10000000;
	srand(time(0));
	long int in_circle = 0;
	double execution_time;
	long int start;
	double pi,x,y;
	int i; 
	
	if (argc > 1) {
		if (!sscanf(argv[1], "%ld", &n)) {
			printf("Zły paramter! Musi być liczbą całkowitą\n");		
		};
	}		

	start = czas();	
	for (i = 0; i < n; i++) {           
         x = ((double)rand() / (RAND_MAX))*2 - 1;
         y = ((double)rand() / (RAND_MAX))*2 - 1;
         if(x*x + y*y <= 1)
         {
             in_circle++;
         }
  }
		
	pi = 	4 * (double)in_circle / n;
	execution_time = (double)(czas() - start)/(double)TIMER_SCALE;
	printf("Dla liczby punktów w kole: %ld \n", n);
	printf("Z math.h \tPI = %.40lf\n", M_PI);
	printf("Wyliczone\tPI = %.40lf\n", pi);
	printf("Czas obliczeń = %f\n", execution_time);
	

	return 0;
}
