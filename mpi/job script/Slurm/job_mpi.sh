#!/bin/bash

#SBATCH -J job_name               # Job name
#SBATCH -p mpi                    # Partition (queue) name
#SBATCH --wait
#SBATCH -N 2                      # number of nodes
#SBATCH --ntasks-per-node=64      # number of mpi tasks (processes) per a node
#SBATCH -n 128                    # number of mpi tasks
#SBATCH -t 01:30:00               # Run time (hh:mm:ss) - 1.5 hours
#SBATCH -o job_stdout.%j.log      # Name of stdout output file (%j expands to jobId)
#SBATCH -e job_stderr.%j.log      # Name of stderr output file (%j expands to jobId)

cd $SLURM_SUBMIT_DIR

module purge
module load intel impi
source /opt/intel/oneapi/setvars.sh --force
export I_MPI_HYDRA_BOOTSTRAP=ssh

mpirun -np 128 -ppn 64 ./matmul_mpi >& matmul_mpi_slurm.log
