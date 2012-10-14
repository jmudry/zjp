#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#include <time.h>
#define TIMER_SCALE  1000000000
long int czas() {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}
int main() {
	long int p = -1, i;
	long int procesow = 4;
	long int przedzial = 100000000;
	long int s,e;
	printf("Start t=%ld\n",s = czas());
	for (i = 0; i < procesow; i++) {
		if (fork() == 0) {
			p = i;
			break;
		}
	}
	if (p >= 0) { // potomek
		long int suma = 0;
		for (i = p*przedzial/procesow;i < (p+1)*przedzial/procesow; i++) {
			suma += i;
		}
		printf("Dla przedzialu <%ld,%ld) suma wynosi %ld\n",
			p*przedzial/procesow,(p+1)*przedzial/procesow, suma);
	} else {
		for ( i = 0; i < procesow; i++)
		wait(NULL);
		printf("Policzylem w %fs\n", (double)(czas() - s)/(double)TIMER_SCALE);
		// zebranie wynikow
	}
	return 0;
}


