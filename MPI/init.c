#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int size, rank, randNum, value, i;
  double my_x, sum;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  srand(time(NULL) + rank);
  randNum = rand();

  // printf("rank: %d Numero: %d \n", rank, randNum);

  for (i = 1; i <= log2(size); i++) {
    if (rank % (int)(pow(2, i)) == pow(2, i) - 1) {
      MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      my_x = my_x + value;
    } else if (rank % (int)(pow(2, i)) == pow(2, i) - pow(2, i - 1) - 1) {
      MPI_Send(&my_x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
  }

  printf("my_x: %d value: %d \n", my_x, value);
  // if(rank==0){

  // }
  MPI_Finalize();
  return 0;
}