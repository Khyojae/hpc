#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#define DATA_SIZE 1

int main(int argc, char** argv)
{
    int i, j, nprocs, myrank, idx;
    int* isend, * irecv;
    int* iscnt, ircnt, * idisp;
    double start, end;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    
    isend = (int*)malloc(sizeof(int) * (nprocs * (nprocs + 1) / 2));
    irecv = (int*)malloc(sizeof(int) * nprocs);
    iscnt = (int*)malloc(sizeof(int) * nprocs);
    idisp = (int*)malloc(sizeof(int) * nprocs);

    idx = 0;

    for (i = 0; idx < (nprocs * (nprocs + 1) / 2); i++)
    {
        for (j = 0; j < i + 1; j++)
        {
            isend[idx] = i + 1;
            idx = idx + 1;
        }
    }

    idisp[0] = 0;

    for (i = 0; i < nprocs; i++)
    {
        iscnt[i] = i + 1;

        if (i > 0)
            idisp[i] = idisp[i - 1] + i;
    }

    memset(irecv, 0x00, sizeof(int) * nprocs);
    ircnt = myrank + 1;

    // rank가 0인 프로세스는 데이터를 다른 크기로 나누어 각 프로세스에게 rank 순서대로 송신
    MPI_Scatterv(isend, iscnt, idisp, MPI_INT, irecv, ircnt, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    for (i = 0; i < nprocs; i++)
        printf("myrank: %d, irecv[%d] = %d\n", myrank, i, irecv[i]);

    printf("myrank %d: elapsed time: %f s\n", myrank, end - start);
    
    MPI_Finalize();

    return 0;
}
