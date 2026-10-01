#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    long i, n;
    double sum, step, pi, x, tsum;
    int cont;
    int myrank, nprocs, ierr, is, ie;
    MPI_Status status;

    cont = 1;
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    while(cont)
    {
        if(myrank == 0)
        {
            printf("Enter the number of intervals (n<1: quits): ");
            fflush(stdout);
            scanf("%ld", &n);
            
            for(i=1; i < nprocs; i++)
                ierr = MPI_Send(&n, 1, MPI_LONG, i, 1, MPI_COMM_WORLD);
        }
        else
        {
            ierr = MPI_Recv(&n, 1, MPI_LONG, 0, 1, MPI_COMM_WORLD, &status);
        }

        if(n <= 0)
        {
            cont = 0;
            break;
        }

        step = 1.0/(double)n;
        sum = 0.0;
        tsum = 0.0;

        for (i = myrank; i < n; i = i + nprocs)
        {
            x = ((double)i + 0.5) * step;
            sum = sum + (4.0 / (1.0 + (x * x))) * step;
        }

        // reduction 연산 결과는 rank가 0인 프로세스에 수신됨
        MPI_Reduce(&sum, &tsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        
        if(myrank == 0)
        {
            pi = tsum;

            printf("---------------------------------\n");
            printf("PI = %.15f (Error = %E)\n", pi, fabs(acos(-1.0) - pi));
            printf("---------------------------------\n");
        }
    }

    ierr = MPI_Finalize();

    return 0;
 }       