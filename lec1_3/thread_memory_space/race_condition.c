#include <stdio.h>
#include <omp.h>

int main(void)
{
    int i = 0;
    int sum = 0;
    int data_size = 10000000;
    double start = 0.0;
    double end = 0.0;

    // 1. 순차 처리
    sum = 0;
    start = omp_get_wtime();

    for(i = 0; i < data_size; i++)
    {
        sum += 1;
    }

    end = omp_get_wtime();  
    printf("1. serial code: sum = %d, elapsed time = %f s\n", sum, end - start);
    
    // 2. 병렬 처리: race condition 발생
    sum = 0;
    start = omp_get_wtime();

    #pragma omp parallel for
    for(i = 0; i < data_size; i++)
    {
        sum += 1;
    }

    end = omp_get_wtime();  
    printf("2. race condition: sum = %d, elapsed time = %f s\n", sum, end - start);

    // 3. 병렬 처리: critical 지시어를 이용한 race condition 해결
    sum = 0;
    start = omp_get_wtime();

    #pragma omp parallel for
    for(i = 0; i < data_size; i++)
    {
        #pragma omp critical
        sum += 1;
    }

    end = omp_get_wtime(); 
    printf("3. critical: sum = %d, elapsed time = %f s\n", sum, end - start);

    // 4. 병렬 처리: reduction 보조 지시어를 이용한 race condition 해결
    sum = 0;
    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for(i = 0; i < data_size; i++)
    {
        sum += 1;
    }

    end = omp_get_wtime(); 
    printf("4. reduction: sum = %d, elapsed time = %f s\n", sum, end - start);

    return 0;
}

