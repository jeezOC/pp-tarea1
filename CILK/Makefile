all: init

init: init.c
	mpicc init.c -o init -lm -L/opt/cilk/lib -lcilkrts -fcilkplus

clean:
	rm -f init
