
all: init

init: init.c
	gcc -fcilkplus -fopenmp -Wall -O3 -o init init.c -lcilkrts -lm -ldl
#	mpicc init.c -o init -lm -L/opt/cilk/lib -lcilkrts -fcilkplus

clean:
	rm -f init
