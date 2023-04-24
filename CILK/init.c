#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cilk/cilk.h>


void intento (int rank,int size, int *sum){
  printf("hello im fakerank=>%d from P=>%d\n",rank,  __cilkrts_get_worker_number());

  int my_value=0;
  int *valueRecived = &my_value;
  int random = (rand() % 100 * rank+1);

  printf("my_rand id=> %d\n", random);

  for (int i = 0; i <= log2(size); i++) {

    if (rank % (int) pow(2, i) == (int) pow(2, i) - 1) {
      //        printf("esta mierda tiene %d\n", *valueRecived);
      //recive(&valueRecived);
      int index = rank - (int)pow(2,i-1);
      printf("Rank_%d recive %d ->  Rank_%d \n ",rank,*valueRecived, index);
      sum += *valueRecived;     
    }

    if (rank % (int) pow(2, i) == (int) pow(2, i) - (int) pow(2, i - 1) - 1) {
      int index = rank + (int)pow(2,i-1);
      //int aux = randoms[index];
      //send(randoms[index]);
      *valueRecived = random;
      printf("Rank_%d envia %d ->  Rank_%d \n ",rank,*valueRecived, index);
    }
  }
}

int main() { 
  int size =4;
  int randoms[size];

  //Inicializar el arreglo con valores aleatorios
 // for (int i = 0; i < size; i++) {
   // randoms[i] = rand() % 100;
  //}
  // Sumar los valores del arreglo en paralelo
  int sum = 0;
#pragma cilk grainsize =1
  cilk_for(int rank = 0; rank< size; ++rank){
    cilk_spawn intento(rank,size, &sum);
  }
  cilk_sync;  
  printf("La suma es: %d\n", sum);

  return 0;
}
