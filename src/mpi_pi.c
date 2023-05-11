#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define NUM_STEPS 100000

int main(int arc, char **argv) {

    int num_proccess, rank;
    double pi, local_pi, step, delta, pi_sum = 0.0;

    //Iniciando MPI
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    step =  1 / (double) NUM_STEPS;

    for(int i = 0; i < NUM_STEPS; i++) {
        delta = (i + 0.5) * step;
        pi_sum += 4.0 / (1.0 + (delta * delta));
    }

    local_pi = step * pi_sum;

    MPI_Reduce(&local_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(rank == 0) {
        printf("pi: %f\n", pi);
    }


    MPI_Finalize();
    return 0;
}