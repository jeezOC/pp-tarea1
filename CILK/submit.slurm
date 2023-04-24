#!/bin/bash
#SBATCH --job-name=init
#SBATCH --output=output.txt
#SBATCH --partition=nu-wide
#SBATCH --ntasks=4
#SBATCH --time=00:05:00

cd $SLURM_SUBMIT_DIR
module load gcc/7.2.0
make

export CILK_NWORKERS=4

srun -n 1 ./init

