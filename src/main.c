#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "benchmark.h"

/**
 * Escreva um programa sequencial paralelo em C com OpenMP, que calcula a média aritmética de um vetor com 500.000.000 (quinhentos milhões) de elementos aleatórios. Os valores variam entre 1 e 100.000. Calcule o speedup e eficiência do seu programa. 
 */

#define CP_NUMBER_THREADS 4
#define CP_VECTOR_MAX_SIZE 500000000
#define CP_VECTOR_MIN_VALUE 100000
#define CP_VECTOR_MAX_VALUE 1

float *cp_random_vector(int min, int max)
{
    float *vector = (float *) malloc(sizeof(float) * CP_VECTOR_MAX_SIZE);
    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        srand((unsigned int)time(NULL));
        #pragma omp for
        for (size_t i = 0; i < CP_VECTOR_MAX_SIZE; i++)
        {
            vector[i] = (float) (rand() % (max - min + 1)) + min;
        }
    }

    return vector;
}

double cp_vector_average(float *vector)
{
    double sum = 0;

    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        #pragma omp for reduction(+: sum)
        for (size_t i = 0; i < CP_VECTOR_MAX_SIZE; i++)
        {
            sum += vector[i];
        }
    }

    return sum / CP_VECTOR_MAX_SIZE;
}

int main()
{
    double etime, stime, average; 
    float *vector;

    stime = omp_get_wtime();

    vector = cp_random_vector(CP_VECTOR_MIN_VALUE, CP_VECTOR_MAX_VALUE);
    average = cp_vector_average(vector);
    printf("average  is %lf\n", average);
    etime = omp_get_wtime();


    printf("start: %.1lf seconds, end: %.1lf seconds\n", stime, etime);
    printf("elapsed time: %.1lf seconds\n", cp_elapsed_time(stime, etime));

    return 0;
}