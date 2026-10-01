#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define DATA_SIZE 1

int main(int argc, char** argv)
{
    int i, nprocs, myrank;
    int *isend, irecv;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    isend = (int *)malloc(sizeof(int) * nprocs);

    for (i = 0; i < nprocs; i++)
        isend[i] = i + 1;

    // rank가 0인 프로세스는 데이터를 같은 크기로 나누어 각 프로세스에게 rank 순서대로 송신
    MPI_Scatter(isend, DATA_SIZE, MPI_INT, &irecv, DATA_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    printf("myrank: %d, irecv = %d\n", myrank, irecv);

    MPI_Finalize();

    return 0;
}