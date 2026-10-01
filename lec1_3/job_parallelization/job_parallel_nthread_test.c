#include <stdio.h>
#include <math.h>
#include <omp.h>

void init_data(float* data, int size)
{
    int i = 0;

    for (i = 0; i < size; i++)
        data[i] = i + 1;
}

void print_data(float* data)
{
    printf("data: %f, %f, %f, %f, %f\n", data[0], data[1], data[2], data[3], data[4]);
}

void calc_sqrt(float* data, int size)
{
    int i = 0;

    for (i = 0; i < size; i++)
        data[i] = sqrt(data[i]);
}

void calc_log(float* data, int size)
{
    int i = 0;

    for (i = 0; i < size; i++)
        data[i] = log(data[i]);
}

int main(void)
{
    double* data1 = NULL;
    double* data2 = NULL;
    int data_size = 100000000;
    double start = 0.0;
    double end = 0.0;

    data1 = (double*)malloc(sizeof(double) * data_size);
    data2 = (double*)malloc(sizeof(double) * data_size);

    init_data(data1, data_size);
    init_data(data2, data_size);

    start = omp_get_wtime();
    
    #pragma omp parallel num_threads(1)     // 병렬 영역 정의(2개의 스레드 생성)
    {
        #pragma omp sections                // 작업 분할 영역 정의
        {
            #pragma omp section
            calc_sqrt(data1, data_size);    // 0번째 스레드에게 작업 A 할당
            #pragma omp section
            calc_log(data2, data_size);     // 1번째 스레드에게 작업 B 할당
        } // 암묵적 동기화에 의해 모든 thread의 실행이 완료될 때까지 기다림
    }
    
    end = omp_get_wtime();

    print_data(data1);
    print_data(data2);
    printf("Elapsed time: %f s\n", end - start);

    free(data1);
    free(data2);

    return 0;
}
