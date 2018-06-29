#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    #pragma omp parallel
    {
	#pragma omp master
	printf("We have initialized %d threads.\n", omp_get_num_threads());
        printf("I am thread %d\n", omp_get_thread_num());
    }

    return 0;
}
