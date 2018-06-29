#!/bin/bash
#SBATCH -J tomas_openmp
#SBATCH -o %J.out
#SBATCH -e %J.err
#SBATCH -n 1
#SBATCH -p small
#SBATCH -t 5
#SBATCH --reservation=summer_school

aprun -e OMP_NUM_THREADS=10 -n 1 -d 10 ./hello
