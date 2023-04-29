#include <stdio.h>
#include <omp.h>
#include <math.h>

#include "benchmark.c"
#include "average_vector_sample.c"

#define CP_NUMBER_THREADS 4

float cp_standard_deviation(float *vector)
{
    
    float standard_deviation, average = cp_serial_average(vector), sum = 0;
    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {

        #pragma omp for firstprivate(sum)
        for(int i = 0; i < CP_VECTOR_MAX_SIZE; i++)
        {
            sum += powf(vector[i] + average, 2);
        }

    }
    
    standard_deviation = sqrtf(sum / CP_VECTOR_MAX_SIZE);
    return standard_deviation;
}

float serial_standard_deviation(float *vector)
{
    float standard_deviation, average = cp_serial_average(vector), sum = 0;

    for(int i = 0; i < CP_VECTOR_MAX_SIZE; i++)
    {
        sum += powf(vector[i] + average, 2);
    }

    standard_deviation = sqrtf(sum / CP_VECTOR_MAX_SIZE);
    return standard_deviation;
}

int main()
{
    printf("%d\n", cp_standard_deviation(cp_random_vector(0, 100)));

    return 0;
}
