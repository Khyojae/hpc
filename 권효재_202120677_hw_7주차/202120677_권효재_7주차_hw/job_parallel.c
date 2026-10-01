#include <stdio.h>

#include <stdlib.h>
#include <math.h>
#include <omp.h>
void init_data(float *data, int size)
{
int i = 0;
for(i = 0; i < size; i++)
data[i] = i + 1;
}

void print_data(float *data)
{
printf("data: %f, %f, %f, %f, %f\n", data[0], data[1], data[2], data[3], data[4]);
}

void calc_sqrt(float *data, int size)
{
int i = 0;
for(i = 0; i < size; i++)
data[i] = sqrtf(data[i]);  
}

void calc_log(float *data, int size)
{
int i = 0;
for(i = 0; i < size; i++)
data[i] = logf(data[i]);  
}


int main(void)
{
float* data1 = NULL;
float* data2 = NULL;

int data_size = 100000000;
double start = 0.0;
double end = 0.0;
data1 = (float *)malloc(sizeof(float) * data_size);
data2 = (float *)malloc(sizeof(float) * data_size);
init_data(data1, data_size);
init_data(data2, data_size);
start = omp_get_wtime();
#pragma omp parallel num_threads(2)
{
#pragma omp sections                
{
#pragma omp section
calc_sqrt(data1, data_size);    
#pragma omp section
calc_log(data2, data_size);     
// 병렬 영역정의(2개의스레드생성)
// 작업 분할영역정의
// 0번째스레드에게작업A 할당
// 1번째스레드에게작업B 할당
} // 암시적동기화에의해모든thread의실행이완료될때까지기다림
}
end = omp_get_wtime();
print_data(data1);
print_data(data2);
printf("Elapsed time: %f s\n", end - start);
free(data1);
free(data2);
return 0;
}
