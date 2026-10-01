#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void init_data(double *data, int size)
{
    int i = 0;
    
    for(i = 0; i < size; i++)
        data[i] = i + 1;
}

void print_data(double *data)
{
    printf("data: %f, %f, %f, %f, %f\n", data[0], data[1], data[2], data[3], data[4]);
}

void calc_sqrt(double *data, int size)
{
    int i = 0;
    
    for(i = 0; i < size; i++)
        data[i] = sqrt(data[i]);  
}

void calc_log(double *data, int size)
{
    int i = 0;
    
    for(i = 0; i < size; i++)
        data[i] = log(data[i]);  
}

int main(void)
{
    double *data1 = NULL;
    double *data2 = NULL;
    int data_size = 100000000;
    clock_t start, end;   
    
    data1 = (double *)malloc(sizeof(double) * data_size);
    data2 = (double *)malloc(sizeof(double) * data_size);

    init_data(data1, data_size);
    init_data(data2, data_size);

    start = clock();
    
    calc_sqrt(data1, data_size);    // 작업 A
    calc_log(data2, data_size);     // 작업 B

    end = clock();
    
    print_data(data1);
    print_data(data2);        
    printf("Elapsed time: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(data1);
    free(data2);

    return 0;
}
