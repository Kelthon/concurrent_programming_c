#include <stdio.h>
#include <omp.h>
#include <math.h>

#include "benchmark.c"
#include "average_vector_sample.c"



int main()
{
    int num_proccess, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proccess);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;



    MPI_Finalize();

    return 0;
}
