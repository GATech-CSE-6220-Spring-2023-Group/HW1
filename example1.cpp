#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int arr[10];
  for (int i = 0; i < 10; i++) {
    arr[i] = world_rank;
  }

  int sum;
  MPI_Reduce(arr, &sum, 10, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (world_rank == 0) {
    printf("Sum: %d\n", sum);
  }

  MPI_Finalize();
}
