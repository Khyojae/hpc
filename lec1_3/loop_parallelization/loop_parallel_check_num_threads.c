#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(void)
{
    double *data;
    int data_size = 100000000;
    int i = 0;

    data = (double *)malloc(sizeof(double) * data_size);

    for (i = 0; i < data_size; i++)
        data[i] = i;                    // 데이터 초기화

    #pragma omp parallel
    {
        for (i = 0; i < data_size; i++)
            data[i] = sqrt(data[i]);    // squre root 계산

        #pragma omp single
        printf("# of threads in parallel region: %d\n", omp_get_num_threads());
    }

    printf("data: %f, %f, %f, %f, %f", data[0], data[1], data[2], data[3], data[4]);    // 결과 출력

    free(data);

    return 0;
}
