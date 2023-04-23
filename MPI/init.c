#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int size, rank, randNum = 0, value_recv = 0;
  int my_x = 0, sum = 0;
  double start = 0, end = 0, elapsed_time = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  start = MPI_Wtime();

  srand((unsigned int)time(NULL));
  my_x = (int)(rand() % 50) * (rank + 1);

  printf("rank:_%d Numero: %d\n", rank, my_x);

  int powParser(int base, int exponent) {
    return (int)pow((double)base, (double)exponent);
  }

  for (int i = 1; i <= log2(size); i++) {
    if ((rank % powParser(2, i)) == (powParser(2, i) - 1)) {
      MPI_Recv(&value_recv, 1, MPI_INT, rank - powParser(2, i - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("Rank_%d \tRECIVE %d \tDE Rank_%d\n---------------------------------------\n\n", rank, value_recv, rank - powParser(2, i - 1));
      my_x = my_x + value_recv;
    } else if ((rank % powParser(2, i)) == (powParser(2, i) - powParser(2, i - 1) - 1)) {
      MPI_Send(&my_x, 1, MPI_INT, rank + powParser(2, i - 1), 0, MPI_COMM_WORLD);
      printf("Rank_%d \tENVIA %d \tA Rank_%d\n---------------------------------------\n\n", rank, my_x, (rank + powParser(2, i - 1)));
    }
  }

  end = MPI_Wtime();

  if (rank == size - 1) {
    printf("------------------\n|   Total: %d   |\n------------------\n\n", my_x);
    elapsed_time = end - start;
    printf("Tiempo de ejecucion: %.6f segundos \n", elapsed_time);
  }

  MPI_Finalize();
  return 0;
}
