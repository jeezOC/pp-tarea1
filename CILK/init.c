#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cilk/cilk.h>

int powParser(int base, int exponent) {
  return (int)pow((double)base, (double)exponent);
}

int main() { 
  int size =5;
  int randoms[size];
  int mail[size];
  //Inicializar el arreglo con valores aleatorios
  for (int i = 0; i < size; i++) {
    int random = (rand() % 50 * i+3);
    printf("load rand in %d = %d\n", i, random);
    randoms[i] = random;
  }
  // Sumar los valores del arreglo en paralelo
  int sum = 0;

  int valR = 0;
  int origin = 0;
  int dest = 0;
#pragma cilk grainsize =1
  cilk_for(int rank = 0; rank< size; ++rank){
    //  printf("hello from P=>%d\n",  __cilkrts_get_worker_number());
    int my_value=0, vr=0, o=0, d=0;
    //int *sum = &my_value;

    // printf("my_rand %d\n", randoms[rank]);

    //for(int j = 0; j<size; ++j){
    // if(rank ==j){
    for (int i = 0; i <= log2(size); i++) {

      if ((rank % powParser(2, i)) == (powParser(2, i) - 1)) {
        //        printf("esta mierda tiene %d\n", *valueRecived);
        //recive(&valueRecived)
        //;

        if(origin  == (rank - powParser(2,i-1))){
          if(dest == rank && origin !=rank){
            //*valR = randoms[origin];
            printf("Rank_%d <- Rank_%d => %d \n",dest,origin,mail[rank]);
            sum+= mail[rank];     
          }
        }
      }

      if ((rank % powParser(2, i)) == (powParser(2, i) - powParser(2, i - 1) - 1)) {
        dest = rank+powParser(2,i-1);
        if(rank!=dest){
          origin = rank;
          
          mail[dest] = randoms[rank];
          printf("Rank_%d -> Rank_%d => %d \n",origin,dest,mail[dest]);
//rank=dest;
        }
      }
      //       }
      //   }
     // sum += my_value;
  }

  if(rank==size-1){printf("La suma es: %d\n", sum);}
  }




  return 0;
}
