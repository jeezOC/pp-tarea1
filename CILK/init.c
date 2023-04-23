#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <math.h>
#include <time.h>
#include <cilk/cilk_api.h>


void loop(int round){
  int rank = __cilkrts_get_worker_number();

  srand((unsigned int)time(NULL));
  int my_x = (int)(rand() % 50) * (rank + 1);

  if(round == rank){
    printf("MY_X is:  %d executed by worker %d\n", my_x, rank);
  }
}

int main() {  
  int size = __cilkrts_get_nworkers();
/* int my_x = 0, sum = 0, randNum = 0, value_recv = 0;*/
/*  
 *  double start_time = 0, end_time = 0, elapsed_time = 0;
 *  start_time = __cilkrts_get_pedigree(); 
 *  */  

  
  for(int i = 0; i <size; i++){
   cilk_spawn loop(i);
  }

/*  printf("rank:_%d Numero: %d\n", rank, my_x);*/
  cilk_sync;
 /* end_time = __cilkrts_get_pedigree();*/

/*  if (rank == size - 1) {
    elapsed_time = end_time - start_time;
    printf("Tiempo de ejecucion: %.6f segundos \n", elapsed_time);
  }
*/

  return 0;
}
