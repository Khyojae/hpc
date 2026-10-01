#!/bin/sh
#PBS -N job_name
#PBS -V
#PBS -q mpi
#PBS -W block=true
#PBS -l select=2:ncpus=64
#PBS -l walltime=00:01:00
#PBS -o job_stdout.log
#PBS -e job_stderr.log

cd $PBS_O_WORKDIR

module purge
module load gnu12 mpich/3.4.3-ofi 

mpirun -np 128 -ppn 64 ./block_comm >& block_comm.log
