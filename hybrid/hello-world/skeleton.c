#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int my_id, omp_rank;
    int provided, required = MPI_THREAD_FUNNELED;

    /* TODO: Initialize MPI with thread support. */
    MPI_Init_thread(&argc, &argv, required, &provided);
    if (provided != required)
    {
        printf("MPI mode with threads not supported!\n");
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    if (provided == MPI_THREAD_MULTIPLE) {
        printf("MPI library supports MPI_THREAD_MULTIPLE\n");
    } else if (provided == MPI_THREAD_SERIALIZED) {
        printf("MPI library supports MPI_THREAD_SERIALIZED\n");
    } else if (provided == MPI_THREAD_FUNNELED) {
        printf("MPI library supports MPI_THREAD_FUNNELED\n");
    } else {
        printf("No multithreading support\n");
    }

    /* TODO: Find out the MPI rank and thread ID of each thread and print
     *       out the results. */

    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    #pragma omp parallel default(shared) private(omp_rank)
    {
        omp_rank = omp_get_thread_num();
        printf("MPI Process %d, thread %d\n", my_id, omp_rank);
    }


    MPI_Finalize();
    return 0;
}
