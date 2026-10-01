#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    long i, n;
    double sum, step, pi, x;
    double *tsum;
    int nprocs, myrank;
    double start, end;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	n = 1000000000;
    tsum = (double *)malloc(sizeof(double)*nprocs);
    memset(tsum, 0x00, sizeof(double)*nprocs);
    
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    step = 1.0 / (double)n;
    sum = 0.0;

    for (i = myrank; i < n; i += nprocs)                // MPI를 통한 루프 병렬화
    {
        x = ((double)i + 0.5) * step;
        sum += ((4.0 / (1.0 + (x * x))) * step);
    }
        
    // rank가 0인 프로세스로 데이터를 취합(gather)
    MPI_Gather(&sum, 1, MPI_DOUBLE, tsum, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if(myrank == 0)
    {
        sum = 0;
        
        for (i = 0; i < nprocs; i++)
            sum = sum + tsum[i];
            
        pi = sum;

        end = MPI_Wtime();

        printf("============================================================\n");
        printf("PI = %.15f (error = %E)\n", pi, fabs(acos(-1.0) - pi));
        printf("Elapsed time: %f s\n", end - start);
        printf("============================================================\n\n");
    }
        
    MPI_Finalize();

    return 0;
}
