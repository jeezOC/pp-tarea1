#!/bin/bash
#SBATCH --job-name=init
#SBATCH --output=output.o%j
#SBATCH --partition=nu-wide
#SBATCH --ntasks=4
#SBATCH --time=00:05:00

cd $SLURM_SUBMIT_DIR

module load anaconda/asdf

mpiexec -n 4 python ./init.py


