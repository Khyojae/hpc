#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#define DATA_SIZE 10000000

int main(int argc, char* argv[])
{
    int nprocs, myrank, i, n;
    double *data_a, *data_b, start, end;
    MPI_Status status;

    data_a = (double *)malloc(sizeof(double)*DATA_SIZE);
    data_b = (double *)malloc(sizeof(double)*DATA_SIZE);
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    if((myrank == 0) || (myrank == 1))
    {
        for(i = 1; i < DATA_SIZE; i++)
            data_a[i] = i * 0.5;

        start = MPI_Wtime();
    }
    
    if(myrank == 0)
    {
        MPI_Recv(data_b, DATA_SIZE, MPI_DOUBLE, 1, 17, MPI_COMM_WORLD, &status);       // ±³Âø(deadlock) ÃÊ·¡
        MPI_Send(data_a, DATA_SIZE, MPI_DOUBLE, 1, 18, MPI_COMM_WORLD);
    }
    else if(myrank == 1)
    {
        MPI_Recv(data_b, DATA_SIZE, MPI_DOUBLE, 0, 18, MPI_COMM_WORLD, &status);       // ±³Âø(deadlock) ÃÊ·¡
        MPI_Send(data_a, DATA_SIZE, MPI_DOUBLE, 0, 17, MPI_COMM_WORLD);
    }
    
    if((myrank == 0) || (myrank == 1))
    {
        end = MPI_Wtime();
        
        n = memcmp(data_a, data_b, sizeof(double)*DATA_SIZE);
        
        if(n == 0)
            printf("process %d: data_a is the same as data_b \n", myrank);
        else
            printf("process %d: data_a is not the same as data_b \n", myrank); 

        printf("process %d: elapsed time: %f s\n", myrank, end - start);
    }

    MPI_Finalize();

    free(data_a);
    free(data_b);

    return 0;
}
