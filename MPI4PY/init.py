from mpi4py import MPI

import random
import math
import time

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()

start = MPI.Wtime()

random.seed(int(time.time()) + rank)
my_x = random.randint(0, 49) * (rank + 1)

print("rank:_%d Numero: %d" % (rank, my_x))

# def powParser(base, exponent):
#     return int(math.pow(base, exponent))

for i in range(1, int(math.log2(size)) + 1):
    if (rank % pow(2, i)) == (pow(2, i) - 1):
        value_recv = comm.recv(source=rank - pow(2, i - 1))
        print("Rank_%d \tRECIVE %d \tDE Rank_%d\n---------------------------------------\n\n" % (rank, value_recv, rank - pow(2, i - 1)))
        my_x += value_recv
    elif (rank % pow(2, i)) == (pow(2, i) - pow(2, i - 1) - 1):
        comm.send(my_x, dest=rank + pow(2, i - 1))
        print("Rank_%d \tENVIA %d \tA Rank_%d\n---------------------------------------\n\n" % (rank, my_x, rank + pow(2, i - 1)))

end = MPI.Wtime()

if rank == size - 1:
    print("------------------")
    print("|   Total: %d   |" % my_x)
    print("------------------\n")
    elapsed_time = end - start
    print("Tiempo de ejecucion: %.6f segundos" % elapsed_time)

MPI.Finalize()