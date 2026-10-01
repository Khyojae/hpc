#!/bin/bash

#SBATCH -J job_name               # Job name
#SBATCH -p omp                    # Partition (queue) name
#SBATCH --wait
#SBATCH -N 1                      # number of nodes
#SBATCH --ntasks-per-node=1       # number of mpi tasks (processes) per a node
#SBATCH --cpus-per-task=4         # number of cpu cores per a task (process)
#SBATCH -n 1                      # number of mpi tasks
#SBATCH -t 01:30:00               # Run time (hh:mm:ss) - 1.5 hours
#SBATCH -o job_stdout.%j.log      # Name of stdout output file (%j expands to jobId)
#SBATCH -e job_stderr.%j.log      # Name of stderr output file (%j expands to jobId)

cd $SLURM_SUBMIT_DIR

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

module purge
module load intel
source /opt/intel/oneapi/setvars.sh --force

./matmul_omp >& matmul_omp.log
