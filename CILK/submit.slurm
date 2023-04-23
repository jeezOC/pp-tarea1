#!/bin/bash
#SBATCH --job-name=init
#SBATCH --output=output.o%j
#SBATCH --partition=nu-wide
#SBATCH --ntasks=4
#SBATCH --time=00:05:00

cd $SLURM_SUBMIT_DIR


module load gcc/7.2.0
module load mpich/3.2.1-gcc-7.2.0

make

srun -np 4 ./init.c


