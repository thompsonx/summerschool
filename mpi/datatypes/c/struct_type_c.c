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
    /* TODO (c): define the datatype for the struct particle  using MPI_Type_create_struct
       You can use MPI_Get_address to compute offsets.
    */
    MPI_Datatype types[] = {MPI_FLOAT, MPI_INT, MPI_CHAR};
    blocklen[0] = 3;
    blocklen[1] = 1;
    blocklen[2] = 2;
    // disp = {0, 3*sizeof(float), 3*sizeof(float) + sizeof(int)};
    MPI_Get_address(&particles[0].coords, &disp[0]);
    MPI_Get_address(&particles[0].charge, &disp[1]);
    MPI_Get_address(&particles[0].label, &disp[2]);
    disp[2] -= disp[0];
    disp[1] -= disp[0];
    disp[0] = 0;
    MPI_Type_create_struct(cnt, blocklen, disp, types, &particletype);
    MPI_Type_commit(&particletype);

    /* TODO (c): check extent (not really necessary on most platforms) That is,
     * check that extent is identical to the distance between two consequtive
     * structs in an array
     * Tip, use MPI_Type_get_extent and  MPI_Get_address
     */

     MPI_Type_get_extent(particletype, &lb, &extent);
     MPI_Get_address(&particles[0], &dist[0]);
     MPI_Get_address(&particles[1], &dist[1]);
     if (extent != (dist[1] - dist[0])) {
       temptype = particletype;
       lb = 0;
       extent = disp[1] - disp[0];
       MPI_Type_create_resized(temptype, lb, extent, &particletype);
       MPI_Type_commit(&particletype);
       MPI_Type_free(&temptype);
     }

     /* communicate using the created particletype */
     t1 = MPI_Wtime();
     if (myid == 0) {
          for (i = 0; i < reps; i++) {
              MPI_Send(particles, n, particletype, 1, i, MPI_COMM_WORLD);
            }
     } else if (myid == 1) {
          for (i = 0; i < reps; i++) {
              MPI_Recv(particles, n, particletype, 0, i, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
          }
    }
    t2 = MPI_Wtime();

    printf("Time: %i, %e \n", myid, (t2 - t1) / (double)reps);
    printf("Check: %i: %s %f %f %f \n", myid, particles[n - 1].label,
           particles[n - 1].coords[0], particles[n - 1].coords[1],
           particles[n - 1].coords[2]);

    //TODO: Free datatype
    MPI_Type_free(&particletype);

    MPI_Finalize();
    return 0;
}
