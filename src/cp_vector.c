#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VECTOR_LENGTH 100

int cp_get_int_random(int min, int max)
{
    int random;

    random = (rand() % max) + min;

    return random;
}

double *cp_gen_vector(int length)
{
    double num, *vector = (double *) malloc(sizeof(double) * length);

    for (size_t i = 0; i < length; i++) {
        num = (rand() % MAX_VECTOR_LENGTH);
        vector[i] = num;
    }
    return vector;
}

int *cp_gen_int_vector(int length)
{
    int num, *vector = (int *) malloc(sizeof(int) * length);

    for (size_t i = 0; i < length; i++) {
        num = (rand() % MAX_VECTOR_LENGTH);
        vector[i] = num;
    }
    return vector;
}

void cp_print_vector(double *vector, int length)
{
    printf("[");

    for (size_t i = 0; i < length; i++) {
        printf("%.5f", vector[i]);
        if(i < length - 1) printf(", ");
    }

    printf("]\n");
}

void cp_print_int_vector(int *vector, int length)
{
    printf("[");

    for (size_t i = 0; i < length; i++) {
        printf("%d", vector[i]);
        if(i < length - 1) printf(", ");
    }

    printf("]\n");
}