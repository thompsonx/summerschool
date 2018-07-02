#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
    typedef struct {
        float coords[3];
        int charge;
        char label[2];
    } particle;

    int n = 1000, cnt = 3, reps = 10000;
    particle particles[n];
    int i, j, myid, ntasks, blocklen[cnt];
    MPI_Datatype particletype, temptype;
    MPI_Aint disp[cnt], dist[2], lb, extent;
    double t1, t2;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* fill in some values for the particles */
    if (myid == 0) {
        for (i = 0; i < 1000; i++) {
            for (j = 0; j < 3; j++) {
                particles[i].coords[j] = (float)rand() / (float)RAND_MAX * 10.0;
            }
            particles[i].charge = 54;
            strcpy(particles[i].label, "Xe");
        }
    }

     /* communicate using the created particletype */

     /* TODO: sending array of structures as MPI_BYTEs */
     t1 = MPI_Wtime();
     if (myid == 0) {
          for (i = 0; i < reps; i++) {
              MPI_Send(particles, sizeof(particle)*n, MPI_BYTE, 1, i, MPI_COMM_WORLD);
            }
     } else if (myid == 1) {
          for (i = 0; i < reps; i++) {
              MPI_Recv(particles, sizeof(particle)*n, MPI_BYTE, 0, i, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
          }
    }
    t2 = MPI_Wtime();

    printf("Time: %i, %e \n", myid, (t2 - t1) / (double)reps);
    printf("Check: %i: %s %f %f %f \n", myid, particles[n - 1].label,
           particles[n - 1].coords[0], particles[n - 1].coords[1],
           particles[n - 1].coords[2]);


    MPI_Finalize();
    return 0;
}
