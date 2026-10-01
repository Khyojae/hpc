#!/bin/bash

#SBATCH -J job_name               # Job name
#SBATCH -p serial                    # Partition (queue) name
#SBATCH --wait
#SBATCH -N 1                      # number of nodes
#SBATCH --ntasks-per-node=1      # number of mpi tasks (processes) per a node
#SBATCH -n 1                    # number of mpi tasks
#SBATCH -t 01:30:00               # Run time (hh:mm:ss) - 1.5 hours
#SBATCH -o job_stdout.%j.log      # Name of stdout output file (%j expands to jobId)
#SBATCH -e job_stderr.%j.log      # Name of stderr output file (%j expands to jobId)

cd $SLURM_SUBMIT_DIR

module purge
module load intel impi
source /opt/intel/oneapi/setvars.sh --force
export I_MPI_HYDRA_BOOTSTRAP=ssh

./matmul_serial >& matmul_serial.log
