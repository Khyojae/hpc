#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int i, nprocs, myrank;
    int* isend, * irecv;
    int iscnt;
    int* ircnt, * idisp;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    isend = (int*)malloc(sizeof(int) * nprocs);
    irecv = (int*)malloc(sizeof(int) * (nprocs * (nprocs + 1) / 2));
    ircnt = (int*)malloc(sizeof(int) * nprocs);
    idisp = (int*)malloc(sizeof(int) * nprocs);

    // 데이터 초기화
    memset(isend, 0x00, sizeof(int) * nprocs);
    memset(irecv, 0x00, sizeof(int) * (nprocs * (nprocs + 1) / 2));
    memset(ircnt, 0x00, sizeof(int) * nprocs);
    memset(idisp, 0x00, sizeof(int) * nprocs);

    for (i = 0; i < myrank + 1; i++)
        isend[i] = myrank + 1;

    iscnt = myrank + 1;

    for (i = 0; i < nprocs; i++)
        ircnt[i] = i + 1;

    for (i = 1; i < nprocs; i++)
        idisp[i] = idisp[i - 1] + i;

    for (i = 0; i < (nprocs * (nprocs + 1) / 2); i++)
        printf("[Before MPI_Allgatherv] rank: %d, irecv[%d]: %d \n", myrank, i, irecv[i]);

    // rank가 0인 프로세스로 데이터를 취합(gather)
    MPI_Allgatherv(isend, iscnt, MPI_INT, irecv, ircnt, idisp, MPI_INT, MPI_COMM_WORLD);

    for (i = 0; i < (nprocs * (nprocs + 1) / 2); i++)
        printf("[After MPI_Allgatherv] rank: %d, irecv[%d]: %d \n", myrank, i, irecv[i]);

    MPI_Finalize();

    return 0;
}
