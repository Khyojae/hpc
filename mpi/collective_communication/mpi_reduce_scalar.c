#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define DATA_SIZE 1

int main(int argc, char** argv)
{
    int i, nprocs, myrank, ista, iend;
    double *a, sum, tsum;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    a = (double *)malloc(sizeof(double)*nprocs*3);

    ista = myrank * 3;
    iend = ista + 3;
    
    for(i = ista; i < iend; i++)
        a[i] = i + 1;

    sum = 0.0;

    for(i = ista; i < iend; i++)
        sum = sum + a[i];

    // reduction 연산 결과는 rank가 0인 프로세스에 수신됨
    MPI_Reduce(&sum, &tsum, DATA_SIZE, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
 
    if(myrank == 0)
        printf("sum = %f\n", tsum);
        
    MPI_Finalize();

    return 0;
}