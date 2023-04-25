#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "benchmark.c"
#include "cp_vector.c"

#define CP_NUMBER_THREADS 4
#define VECTOR_SIZE 100

int cp_serial_count(int *vector, int length, int find)
{
    int count = 0;

    for(size_t i = 0; i < length; i++)
    {
        if(vector[i] == find) count++;
    }

    return count;
}

int cp_count(int *vector, int length, int find)
{
    int count = 0;

    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        #pragma omp for reduction(+: count)
        for(size_t i = 0; i < length; i++)
        {
            if(vector[i] == find) count++;
        }
    }

    return count;
}
int main()
{
    time_t t;
    srand(time(NULL));

    int find = cp_get_int_random(100, 1000), 
    *numbers = cp_gen_int_vector(VECTOR_SIZE),
    count = 0;

    double parallel_elapsed_time, parallel_start_time, parallel_end_time, serial_elapsed_time, serial_start_time, serial_end_time;

    parallel_start_time = omp_get_wtime();
    count = cp_serial_count(numbers, VECTOR_SIZE, find);
    parallel_end_time = omp_get_wtime();
    parallel_elapsed_time = cp_elapsed_time(parallel_start_time, parallel_end_time);



    serial_start_time = omp_get_wtime();
    count = count = cp_count(numbers, VECTOR_SIZE, find);
    serial_end_time = omp_get_wtime();
    serial_elapsed_time = cp_elapsed_time(serial_start_time, serial_end_time);

    printf("speedup: %.2lf, efficiency: %.2lf\n", cp_speedup(serial_elapsed_time, parallel_elapsed_time), cp_efficiency(serial_elapsed_time, parallel_elapsed_time, CP_NUMBER_THREADS));
    return 0;
}