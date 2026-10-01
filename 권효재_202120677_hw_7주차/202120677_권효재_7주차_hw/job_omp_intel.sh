#!/bin/sh
#PBS -N job_name
#PBS -V
#PBS -q omp
#PBS -W block=true
#PBS -l select=1:ncpus=4
#PBS -l walltime=00:01:00

#PBS -o matmul_omp.out
#PBS -e matmul_omp.err

cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=4


module purge
module load intel
source /opt/intel/oneapi/setvars.sh --force

./job_parallel  >& job_parallel.log

