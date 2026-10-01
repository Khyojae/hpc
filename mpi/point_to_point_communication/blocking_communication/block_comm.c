#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define DATA_A_SIZE 100
#define DATA_B_SIZE 200

int main(int argc, char* argv[])
{
    int nprocs, myrank, i, n, count;
    float data_a[DATA_A_SIZE], data_b[DATA_B_SIZE];
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    for (i = 0; i < DATA_A_SIZE; i++)
        data_a[i] = i * 0.5;

    if(myrank == 0)                                 
    {
        // rank 번호가 0인 프로세스가 다른 프로세스에게 데이터 송신
        for (i = 1; i < nprocs; i++)
            MPI_Send(data_a, DATA_A_SIZE, MPI_FLOAT, i, 55, MPI_COMM_WORLD);    
    }
    else
    {
        // rank 번호가 0인 프로세스이 보낸 데이터를 rank 번호가 0이 아닌 프로세스가 수신
        MPI_Recv(data_b, DATA_B_SIZE, MPI_FLOAT, 0, 55, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_FLOAT, &count);
        printf("process %d received %d elements of data_a from process %d\n", myrank, count, status.MPI_SOURCE);
        
        // 송신된 데이터와 수신된 데이터가 같은지 확인
        n = memcmp(data_a, data_b, sizeof(float)*DATA_A_SIZE);
        
        if(n == 0)
            printf("process %d: data_a is the same as data_b \n", myrank);
        else
            printf("process %d: data_a is not the same as data_b \n", myrank);        
    }

    MPI_Finalize();

    return 0;
}
