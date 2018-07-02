#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int array[8][8];
    //TODO: Declare a variable storing the MPI datatype

    int i, j;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize arrays
    if (rank == 0) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                array[i][j] = (i + 1) * 10 + j + 1;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                array[i][j] = 0;
            }
        }
    }

    if (rank == 0) {
        printf("Data in rank 0\n");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    //TODO: Create datatype that describes one column. Use MPI_Type_vector.
    MPI_Datatype vector;
    MPI_Type_vector(8, 1, 8, MPI_INT, &vector);
    MPI_Type_commit(&vector);
    //TODO: Send first column of matrix form rank 0 to rank 1
    if (rank == 0)
        MPI_Send(array, 1, vector, 1, 0, MPI_COMM_WORLD);
    else if (rank == 1)
        MPI_Recv(&array[0][1], 1, vector, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


    //TODO: free datatype
    MPI_Type_free(&vector);


    // Print out the result on rank 1
    // The application is correct if the first column has the values of rank 0
    if (rank == 1) {
        printf("Received data\n");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}
