#include <stdio.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    int required = MPI_THREAD_MULTIPLE;
    int provided;
    
    MPI_Init_thread(&argc, &argv, required, &provided);

    if (provided != required)
    {
        printf("MPI Thread mode not supported\n");
        MPI_Abort(MPI_COMM_WORLD, -1);
        return 0;
    }

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int tid, received;
    #pragma omp parallel default(shared) private(received, tid)
    {
        tid = omp_get_thread_num();
        if (rank == 0)
        {
            MPI_Send(&tid, 1, MPI_INT, 1, tid, MPI_COMM_WORLD);
            MPI_Send(&tid, 1, MPI_INT, 2, tid, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Recv(&received, 1, MPI_INT, 0, tid, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d, thread %d \t received <- %d\n", rank, tid, received);
        }
    }

    MPI_Finalize();

    return 0;
}

