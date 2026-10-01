#!/bin/sh

#PBS -N job_name
#PBS -V
#PBS -q omp
#PBS -W block=true
#PBS -l select=1:ncpus=3
#PBS -l walltime=00:01:00
#PBS -o job_stdout.log
#PBS -e job_stderr.log

cd $PBS_O_WORKDIR
export OMP_NUM_THREADS=3

module purge
module load intel
source /opt/intel/oneapi/setvars.sh --force

./mid_exam_prog2 >& mid_exam_prog2.log

