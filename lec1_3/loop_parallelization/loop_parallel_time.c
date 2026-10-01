#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(void)
{
    double *data;
    int data_size = 100000000;
    int i = 0;
    double start = 0.0;
    double end = 0.0;
    
    data = (double *)malloc(sizeof(double) * data_size);

    for (i = 0; i < data_size; i++)
        data[i] = i;                    // 데이터 초기화

    start = omp_get_wtime();
    
    #pragma omp parallel num_threads(2) // 2개의 스레드 생성
    {
        for (i = 0; i < data_size; i++)
            data[i] = sqrt(data[i]);    // squre root 계산
    }

    end = omp_get_wtime();

    printf("data: %f, %f, %f, %f, %f\n", data[0], data[1], data[2], data[3], data[4]);  // 결과 출력
    printf("Elapsed time: %f s\n", end - start);
    free(data);

    return 0;
}