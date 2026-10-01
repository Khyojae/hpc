#!/bin/sh
#PBS -N job_name
#PBS -V
#PBS -q omp
#PBS -W block=true
#PBS -l select=1:ncpus=4
##PBS -l select=1:ncpus=4:mpiprocs=1:ompthreads=4
#PBS -l walltime=00:01:00
#PBS -o job_stdout.log
#PBS -e job_stderr.log

cd $PBS_O_WORKDIR
#export OMP_NUM_THREADS=4

module purge
module load gnu12

./helloworld_p >& helloworld_p.log
