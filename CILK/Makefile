all: init

init: init.c
	mpicc init.c -o init -lm -fcilkplus
 

clean:
	rm -f init
