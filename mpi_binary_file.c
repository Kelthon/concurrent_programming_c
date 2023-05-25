#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define FILE_SIZE 1000

int *gerar_vetor_binario(int n) {
  int *vetor;
  int i; 
  vetor = (int *)malloc(sizeof(int) * n);
  for (i=0;i<n;i++) {
    int num = rand() % 2;
    vetor[i] = num;
  }
  return vetor;
}

int main(int arc, char **argv) {

  int rank;
  int nprocs;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  srand(time(NULL)*(rank + 1));
  
  int ones = 0;
  int *total_ones = (int *) calloc(nprocs, sizeof(int));
  int subvector_size = (int) ceil(FILE_SIZE / (int) nprocs);
  int *subvector = (int *) calloc(subvector_size, sizeof(int));
  int *vector = gerar_vetor_binario(FILE_SIZE);

  MPI_Gather(vector, FILE_SIZE, MPI_INT, subvector, subvector_size, MPI_INT, 0, MPI_COMM_WORLD);

  for(int i = 0; i < subvector_size; i++) {
    if(subvector[i] == 1) ones++;
  }

  MPI_Scatter(subvector, subvector_size, MPI_INT, total_ones, nprocs, MPI_INT, 0, MPI_COMM_WORLD);
  
  for(int i = 0; i < nprocs; i++) {
    ones += total_ones[i];
  }

  if(ones % 2 != 0) {
    vector = (int *) realloc(vector, FILE_SIZE+1);
    vector[FILE_SIZE+1] = 1;
  }


  free(vector);
  free(subvector);
  free(total_ones);
  MPI_Finalize();
  return 0;
}