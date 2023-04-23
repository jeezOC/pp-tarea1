#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int size, rank, randNum = 0, value_recv = 0;
  int my_x = 0, sum = 0;
  double start = 0, end = 0, elapsed_time = 0;



  srand((unsigned int)time(NULL));
  my_x = (int)(rand() % 50) * (rank + 1);

  printf("rank:_%d Numero: %d\n", rank, my_x);


  end = __cilkrts_get_walltime();

  if (rank == size - 1) {
    elapsed_time = end - start;
    printf("Tiempo de ejecucion: %.6f segundos \n", elapsed_time);
  }

  return 0;
}