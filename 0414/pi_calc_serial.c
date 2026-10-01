#include <stdio.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv)
{
    long i, n;
    double sum, step, pi, x;
    clock_t start, end;

    n = 1000000000;
    
    start = clock();

    step = 1.0 / (double)n;
    sum = 0.0;

    for (i = 0; i < n; i++)
    {
        x = ((double)i + 0.5) * step;
        sum += ((4.0 / (1.0 + (x * x))) * step);
    }

    pi = sum;

    end = clock();

    printf("============================================================\n");
    printf("PI = %.15f (error = %E)\n", pi, fabs(acos(-1.0) - pi));
    printf("Elapsed time: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("============================================================\n\n");

    return 0;
}
