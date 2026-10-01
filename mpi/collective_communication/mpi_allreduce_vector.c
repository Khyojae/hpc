#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define DATA_SIZE 2

int main(int argc, char** argv)
{
    int i, nprocs, myrank;
    double *a, *sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    a = (double *)malloc(sizeof(double) * DATA_SIZE);
    sum = (double *)malloc(sizeof(double) * DATA_SIZE);

    for (i = 0; i < DATA_SIZE; i++)
        a[i] = (i * nprocs) + (myrank + 1);

    // reduction 연산 결과는 모든 프로세스에 수신됨
    MPI_Allreduce(a, sum, DATA_SIZE, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    for (i = 0; i < DATA_SIZE; i++)
        printf("myrank: %d, sum[%d] = %f \n", myrank, i, sum[i]);

    MPI_Finalize();

    return 0;
}