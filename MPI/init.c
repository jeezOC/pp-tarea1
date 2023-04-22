#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[])
{

  int size, rank, randNum, sum, my_x;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  srand(time(NULL) + rank);
  randNum = rand();

  printf("rank: %d Numero: %d \n", rank, randNum);

  for (i = 1; i <= log2(n); i++)
  {
    if (rank % pow(2, i) == pow(2, i) - 1)
    {
      MPI_recv();
      my_x = my_x + value;
    }
    else if (rank % pow(2, i) == pow(2, i) - pow(2, i - 1) - 1)
    {
      MPI_send(&my_x, 1, MPI_INT, 1, 0);
      send my_x to processor ID + pow(2, i - 1);
    }
  }

  // if(rank==0){

  // }
  MPI_Finalize();
  return 0;
}