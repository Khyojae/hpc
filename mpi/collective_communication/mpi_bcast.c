#include <stdio.h>
#include <mpi.h>
#define DATA_SIZE 4

int main(int argc, char* argv[])
{
    int i, nprocs, myrank;
    int imsg[DATA_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    // 데이터 초기화 
    if(myrank == 0)
        for(i = 0; i < DATA_SIZE; i++)
            imsg[i] = i + 1;
    else
        for(i = 0; i < DATA_SIZE; i++)
            imsg[i] = 0;
        
    for(i = 0; i < DATA_SIZE; i++)
        printf("[Before MPI_Bcast] rank: %d, imsg[%d]: %d \n", myrank, i, imsg[i]);

    // rank가 0인 프로세스가 데이터를 방송(broadcast)
    MPI_Bcast(imsg, DATA_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    
    for(i = 0; i < DATA_SIZE; i++)
        printf("[After MPI_Bcast] rank: %d, imsg[%d]: %d \n", myrank, i, imsg[i]);

    MPI_Finalize();

    return 0;
}
