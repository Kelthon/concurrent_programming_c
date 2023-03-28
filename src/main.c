#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel num_threads(2)
    {
        #pragma omp for
        for (size_t i = 0; i < 100000; i++)
        {
            printf("%d, \n", i);
        }   
    }
    
    return 0;
}