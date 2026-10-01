#include <stdio.h>
#include <omp.h>

int main()
{
    float A[5] = { 1,2,3,4,5 };
    printf("main memory %.1f, %.1f, %.1f, %.1f, %.1f\n", A[0], A[1], A[2], A[3], A[4]);

    #pragma omp parallel num_threads(4) private(A)
    {
        A[0] = 7;
        A[1] = 7;

        printf("main memory %.1f, %.1f, %.1f, %.1f, %.1f\n", A[0], A[1], A[2], A[3], A[4]);
    }

    printf("main memory %.1f, %.1f, %.1f, %.1f, %.1f\n", A[0], A[1], A[2], A[3], A[4]);

    return 0;
}

