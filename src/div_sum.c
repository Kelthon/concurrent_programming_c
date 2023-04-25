/**
    Write a program that when give a number greather than one billion, its calculates the sum of all you divisors
*/

#include <stdio.h>
#include <omp.h>
#include "benchmark.c"

#define ONE_BILLION 1000000000
#define CP_NUMBER_THREADS 4

int cp_serial_div_sum(int number)
{
    int sum = 0;

    for(int i = 1; i <= number; i++)
    {
        if(number % i == 0)
        {
            sum += i;
        }
    }

    return sum;
}

int cp_div_sum(int number)
{
    int sum = 0;
    
    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        #pragma omp for reduction(+: sum)
        for(int i = 1; i <= number; i++)
        {
            if(number % i == 0)
            {
                sum += i;
            }
        }
    }

    return sum;
}

int main()
{
    int sum, value = ONE_BILLION * 1.5;
    double parallel_elapsed_time, parallel_start_time, parallel_end_time, serial_elapsed_time, serial_start_time, serial_end_time;

    parallel_start_time = omp_get_wtime();
    sum = cp_div_sum(value);
    parallel_end_time = omp_get_wtime();
    parallel_elapsed_time = cp_elapsed_time(parallel_start_time, parallel_end_time);



    serial_start_time = omp_get_wtime();
    sum = cp_serial_div_sum(value);
    serial_end_time = omp_get_wtime();
    serial_elapsed_time = cp_elapsed_time(serial_start_time, serial_end_time);

    printf("speedup: %.2lf, efficiency: %.2lf\n", cp_speedup(serial_elapsed_time, parallel_elapsed_time), cp_efficiency(serial_elapsed_time, parallel_elapsed_time, CP_NUMBER_THREADS));
    return 0;
}
