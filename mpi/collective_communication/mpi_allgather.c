#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int i, nprocs, myrank;
    int isend = 0;
    int* irecv;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    irecv = (int*)malloc(sizeof(int) * nprocs);

    // 데이터 초기화 
    memset(irecv, 0x00, sizeof(int) * nprocs);
    isend = myrank + 1;

    for (i = 0; i < nprocs; i++)
        printf("[Before MPI_Allgather] rank: %d, irecv[%d]: %d \n", myrank, i, irecv[i]);

    // rank가 0인 프로세스로 데이터를 취합(gather)
    MPI_Allgather(&isend, 1, MPI_INT, irecv, 1, MPI_INT, MPI_COMM_WORLD);

    for (i = 0; i < nprocs; i++)
        printf("[After MPI_Allgather] rank: %d, irecv[%d]: %d \n", myrank, i, irecv[i]);

    MPI_Finalize();

    return 0;
}