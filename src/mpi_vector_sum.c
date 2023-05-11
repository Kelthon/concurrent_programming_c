#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define MAX_VECTOR_LENGTH 1000

double *gen_vector(int length) {
    double num, *vector = (double *) malloc(sizeof(double) * length);

    for (size_t i = 0; i < length; i++) {
        num = (rand() % MAX_VECTOR_LENGTH);
        vector[i] = num;
    }

    return vector;
}

int main(int arc, char **argv) {

    int num_proccess, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    
    timer_t default_timer;
    srand(time(NULL) * (rank + 1));

    double sum = 0;
    int length = 1000;
    double * vector;

    if(rank == 0) {
        vector = gen_vector(length);
        MPI_Bcast(&vector, length, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        MPI_Recv(&sum, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Sum 1: %lf", sum);
        MPI_Recv(&sum, 1, MPI_DOUBLE, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Sum 2: %lf", sum);
    }
    else if(rank == 1) {
        MPI_Recv(&vector, length, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        for(int i = 0; i < length; i++) {
            sum += vector[i];
        }

        MPI_Send(&sum, length, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
    }
    else if(rank == 2) {
        MPI_Recv(&vector, length, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i = 0; i < length; i++) {
            sum += 2 * vector[i];
        }

        MPI_Send(&sum, length, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }

    free(vector);
    vector = NULL;
    MPI_Finalize();
    return 0;
}