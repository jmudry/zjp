#include <omp.h>
#include <stdio.h>

// cc first.c -fopenmp
int main(){
		int i;
#pragma omp parallel for
		for (i = 0; i < 4; i++) {
		printf("Jestem %d, i=%d\n", omp_get_thread_num(), i);
		}

	return 0;
}
