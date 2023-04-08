#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "benchmark.c"

#define NUM_STEPS 300000000
#define CP_NUMBER_THREADS 4

double serial_get_pi()
{
    double x, pi, step, sum = 0;
    step = 1.0 / (double) NUM_STEPS;

    for (int i = 0; i < NUM_STEPS; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    return pi;
}

double cp_get_pi()
{
    double x, pi, step, sum = 0;
    step = 1.0 / (double) NUM_STEPS;
    
    #pragma omp parallel private(x) num_threads(CP_NUMBER_THREADS)
    {
        #pragma omp for reduction (+:sum)
        for (int i = 0; i < NUM_STEPS; i++)
        {
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }

        pi = step * sum;
    }
    return pi;
}

int main() 
{
    double pi, parallel_elapsed_time, parallel_start_time, parallel_end_time, serial_elapsed_time, serial_start_time, serial_end_time;

    // Parallel
    parallel_start_time = omp_get_wtime();
    pi = cp_get_pi();
    parallel_end_time = omp_get_wtime();
    parallel_elapsed_time = cp_elapsed_time(parallel_start_time, parallel_end_time);
    printf("parallel pi: %.2f elapsed time: %.1lf seconds\n", pi, parallel_elapsed_time);
    
    // Serial
    serial_start_time = omp_get_wtime();
    pi = serial_get_pi();
    serial_end_time = omp_get_wtime();
    serial_elapsed_time = cp_elapsed_time(serial_start_time, serial_end_time);
    printf("serial pi: %.2f elapsed time: %.1lf seconds\n", pi, serial_elapsed_time);

    // Conclusion
    printf("speedup: %.2lf, efficiency: %.2lf\n", cp_speedup(serial_elapsed_time, parallel_elapsed_time), cp_efficiency(serial_elapsed_time, parallel_elapsed_time, CP_NUMBER_THREADS));

    return 0;
}