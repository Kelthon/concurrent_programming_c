#include <stdio.h>
#include <omp.h>

#include "benchmark.c"
#include "average_vector_sample.c"

#define CP_NUMBER_THREADS 4

int cp_grather_index(float *vector)
{
    int index = 0;
    int greater = -1;

    #pragma omp parallel num_threads(CP_NUMBER_THREADS)
    {
        #pragma omp for firstprivate(greater) shared(index)
        for(int i = 0; i < CP_VECTOR_MAX_SIZE; i++)
        {
            if(vector[i] > greater)
            {
                greater = vector[i];
                index = i;
            }
        }
    }
}

int serial_grather_index(float *vector)
{
    int index = 0;
    int greater = -1;

    for(int i = 0; i < CP_VECTOR_MAX_SIZE; i++)
    {
        if(vector[i] > greater)
        {
            greater = vector[i];
            index = i;
        }
    }

    return index;
}

int main()
{
    srand(time(NULL));
    float *vector = cp_random_vector(0, 100);

    printf("%d\n", cp_grather_index(vector));

    return 0;
}
