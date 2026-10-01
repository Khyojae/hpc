#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main(int argc, char** argv)
{
    long i, n;
    double sum, step, pi, x;
    double start, end;

    n = 1000000000;
    
    start = omp_get_wtime();

    step = 1.0 / (double)n;
    sum = 0.0;

    #pragma omp parallel for reduction(+:sum) private(x) num_threads(4)

    for (i = 0; i < n; i++)
    {
        x = ((double)i + 0.5) * step;
        sum += ((4.0 / (1.0 + (x * x))) * step);
    }

    pi = sum;

    end = omp_get_wtime();

    printf("============================================================\n");
    printf("PI = %.15f (error = %E)\n", pi, fabs(acos(-1.0) - pi));
    printf("Elapsed time: %f s\n", (end - start) );
    
    printf("============================================================\n\n");

    return 0;
}
