#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    long i, n;
    double sum, tsum, step, pi, x;
    int nprocs, myrank;
    double start, end;
    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    n = 1000000000;
    
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    step = 1.0 / (double)n;
    sum = 0.0;

    for (i = myrank; i < n; i += nprocs)                // MPI를 통한 루프 병렬화
    {
        x = ((double)i + 0.5) * step;
        sum += ((4.0 / (1.0 + (x * x))) * step);
    }

    if(myrank == 0)
    {
        tsum = sum;

        for (i = 1; i < nprocs; i++)
        {
            ???;
            ???;
            tsum = tsum + sum;
        }

        pi = tsum;

        end = MPI_Wtime();

        printf("============================================================\n");
        printf("PI = %.15f (error = %E)\n", pi, fabs(acos(-1.0) - pi));
        printf("Elapsed time: %f s\n", end - start);
        printf("============================================================\n\n");
    }
    else
    {
        ???;
        ???;
    }
        
    MPI_Finalize();

    return 0;
}

