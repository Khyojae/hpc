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
module load intel impi
source /opt/intel/oneapi/setvars.sh --force
export I_MPI_HYDRA_BOOTSTRAP=ssh

mpirun -np 128 -ppn 64 ./block_comm >& block_comm.log
