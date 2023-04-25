#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cilk/cilk.h>

int powParser(int base, int exponent) {
  return (int)pow((double)base, (double)exponent);
}

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
      if ((rank % powParser(2, i)) == (powParser(2, i) - 1)) {

        if(origin  == (rank - powParser(2,i-1))){
          if(dest == rank && origin !=rank){
            printf("Rank_%d <- Rank_%d => %d \n",dest,origin,val_r);
            my_val += val_r;
          }
        }
      }

      if ((rank % powParser(2, i)) == (powParser(2, i) - powParser(2, i - 1) - 1)) {
        dest = rank+powParser(2,i-1);
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
  int size =__cilkrts_get_nworkers();
  printf("size=>%d",size);

  for(int rank=0; rank<size; rank++){
    cilk_spawn addition(rank, size);
  } 
  cilk_sync;

  printf("total =>%d \n", sum);
  return 0;
}
