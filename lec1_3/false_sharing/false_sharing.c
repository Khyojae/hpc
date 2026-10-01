#include <stdio.h>
#include <omp.h>
#define MAX 100000000
#define CACHE_LINE_SIZE 8

int main() 
{
    int i = 0;
    double start = 0.0, end = 0.0, total = 0.0;
    double Data[MAX] = {0,};
    double sum[2] = {0,};
    double sum_[2][CACHE_LINE_SIZE] = {0,};

    omp_set_num_threads(2);

    #pragma omp parallel for
    for(int i = 0; i < MAX; i++)
        Data[i] = i + 1;
    
    // 1. False sharing 발생
    start = omp_get_wtime();
    
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();

        #pragma omp for
        for(i = 0; i < MAX; i++)
            sum[ID] += Data[i];
    }

    total = sum[0] + sum[1];
    end = omp_get_wtime();
    printf("[false sharing] elapsed time: %f sec, result: %.0f\n", end-start, total);

    // 2. False sharing 해결 (thread들의 공유변수가 캐시라인에 들어오지 않도록 함)
    start = omp_get_wtime();

    #pragma omp parallel
    {
        int ID = omp_get_thread_num();

        #pragma omp for
        for(i = 0; i < MAX; i++)
            sum_[ID][0] += Data[i]; 
    }

    total = sum_[0][0] + sum_[1][0];
    end = omp_get_wtime();
    printf("[No false sharing] elapsed time: %f sec, result: %.0f\n", end-start, total);

    return 0;
}

