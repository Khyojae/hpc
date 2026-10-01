#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(void)
{
    double* data;
    int data_size = 100000000;
    int thread_size = 2;
    int i = 0;
    double start = 0.0;
    double end = 0.0;

    data = (double*)malloc(sizeof(double) * data_size);

    for (i = 0; i < data_size; i++)
        data[i] = i;                    // 데이터 초기화

    printf("Default number of threads: %d\n", omp_get_max_threads());  // default로 설정된 스레드 수 확인

    start = omp_get_wtime();

	#pragma omp parallel for num_threads(thread_size)   // 2개의 스레드 생성
    for (i = 0; i < data_size; i++)     
        data[i] = sqrt(data[i]);        // squre root 계산
    
    end = omp_get_wtime();

    printf("data: %f, %f, %f, %f, %f\n", data[0], data[1], data[2], data[3], data[4]);  // 결과 출력
    printf("Number of threads: %d\n", thread_size);
    printf("Elapsed time: %f s\n", end - start);
	
    free(data);

    return 0;
}
