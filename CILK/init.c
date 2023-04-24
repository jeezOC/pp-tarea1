#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <math.h>
#include <time.h>
#include <cilk/cilk_api.h>
#include <string.h>

// Estructura de datos compartida
typedef struct shared_data {
    int *data; // Arreglo de datos
    int count; // Cantidad de datos en el arreglo
} shared_data_t;

void *memcpy(void* dest, const void* src, size_t n) {
    char *dest_ptr = (char *)dest;
    const char *src_ptr = (const char *)src;
    
    for (size_t i = 0; i < n; i++) {
        dest_ptr[i] = src_ptr[i];
    }
    
    return dest;
}


// Función que simula MPI_Send
void my_send(shared_data_t *sdata, int dest) {
    // Enviar los datos al proceso destino
    cilk_spawn memcpy(sdata[dest].data, sdata->data, sdata->count * sizeof(int));
    cilk_sync;
}

void my_MPI_Send(void* data, int count, int dest) {
    for (int i = 0; i < dest; i++) {
        cilk_spawn my_send(data, i);
    }
    cilk_sync;
}

// Función que simula MPI_Recv
void my_recv(shared_data_t *sdata, int source) {
    // Recibir los datos del proceso origen
    cilk_spawn memcpy(sdata->data, sdata[source].data, sdata->count * sizeof(int));
    cilk_sync;
}

void my_MPI_Recv(void* data, int count, int source) {
    cilk_spawn my_recv(data, source);
    cilk_sync;
}

int powParser(int base, int exponent) {
  return (int)pow((double)base, (double)exponent);
}

int main(int argc, char *argv[]){
  int value_recv = 0;
  int size = __cilkrts_get_nworkers();

  int rank = __cilkrts_get_worker_number();

  srand((unsigned int)time(NULL));
  int my_x = (int)(rand() % 50) * (rank + 1);

  if(round == rank){ //areglar loop
    printf("MY_X is:  %d executed by worker %d\n", my_x, rank);
  }
  
  cilk_for (int k = 0; k <= log2(size); k++) {
      if (rank % powParser(2, k) == powParser(2, k) - 1) {
  	    //receive
        my_MPI_Recv(&value_recv, 1, rank - powParser(2, k - 1));
        printf("Rank_%d \tRECIVE %d \tDE Rank_%d\n---------------------------------------\n\n", rank, value_recv, rank - powParser(2, k - 1));
        my_x += value_recv;
      }
      if (rank % powParser(2, k) == powParser(2, k) - powParser(2, k) - 1) {
      	//send
        my_MPI_Send(&my_x, 1, rank + powParser(2, k - 1));
        printf("Rank_%d \tENVIA %d \tA Rank_%d\n---------------------------------------\n\n", rank, my_x, (rank + powParser(2, k - 1)));
      }
  }
  return 0;
}