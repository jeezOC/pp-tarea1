#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cilk/cilk.h>
#include <time.h>
#include <sys/time.h>

int process(int rank, int size){
  int my_val=0;
  if(rank==__cilkrts_get_worker_number()){
    srand((unsigned int)time(NULL));
    int random = (rand() % 50 * rank+1);
    my_val=random;
    printf("Rank_%d set my_val = %d\n", rank, my_val);
    int val_r =0, dest=0, origin=0;

    printf("Hola soy fake_rank_%d desde el worker_%d\n", rank, __cilkrts_get_worker_number());

    for (int i = 0; i <= log2(size); i++) {
      if ((rank % (int)pow(2, i)) == ((int)pow(2, i) - 1)) {

        if(origin  == (rank - (int)pow(2,i-1))){
          if(dest == rank && origin !=rank){
            printf("Rank_%d <- Rank_%d => %d \n",dest,origin,val_r);
            my_val += val_r;
          }
        }
      }

      if ((rank % (int)pow(2, i)) == ((int)pow(2, i) - (int)pow(2, i - 1) - 1)) {
        dest = rank+(int)pow(2,i-1);
        if(rank!=dest){
          origin = rank;
          printf("Rank_%d -> Rank_%d => %d \n",origin,dest,my_val);
          val_r=my_val;
        }
      }
    }
  }
  return my_val;
}

int sum = 0;

void addition(int rank, int size){
  sum += process(rank, size);
}

int main(int argc, char *argv[]) { 
  struct timeval start_time, end_time;
  double elapsed_time;
  gettimeofday(&start_time, NULL);

  int size =__cilkrts_get_nworkers();
  printf("size=>%d\n\n",size);

  for(int rank=0; rank<size; rank++){
    cilk_spawn addition(rank, size);
  } 

  cilk_sync;
  printf("TOTAL=> %d\n\n", sum);

  gettimeofday(&end_time, NULL);
  elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
    (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

  printf("Tiempo de ejecución: %f segundos\n", elapsed_time);

  return 0;
}
