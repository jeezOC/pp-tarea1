#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int size = __cilkrts_get_nworkers();
  int rank = __cilkrts_get_worker_number();
  int my_x = 0, sum = 0, randNum = 0, value_recv = 0;

  double start_time = 0, end_time = 0, elapsed_time = 0;
  

  /*start_time = __cilkrts_get_walltime();*/
/*  srand((unsigned int)time(NULL));
  my_x = (int)(rand() % 50) * (rank + 1);*/

  printf("rank:_%d Numero: %d\n", rank, my_x);
  cilk_for(int i = 0; i <size; i++){
    printf("Task %d executed by worker %d\n", i, rank);
  }

/*  end_time = __cilkrts_get_walltime();

  if (rank == size - 1) {
    elapsed_time = end_time - start_time;
    printf("Tiempo de ejecucion: %.6f segundos \n", elapsed_time);
  }
*/
  return 0;
}
