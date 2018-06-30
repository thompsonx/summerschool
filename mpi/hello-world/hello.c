#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello from Finland! I am process %d\n", rank);

    if (rank == 0)
    {
        int n;
        MPI_Comm_size(MPI_COMM_WORLD, &n);
        printf("Total number of executed process is %d\n", n);
    }

    MPI_Finalize();

    return 0;
}
