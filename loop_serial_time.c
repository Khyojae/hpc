#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void)
{
    double *data;
    int data_size = 100000000;
    int i = 0;
    clock_t start, end;
    
    data = (double *)malloc(sizeof(double) * data_size);

    for (i = 0; i < data_size; i++)
        data[i] = i;

    start = clock();

    for(i = 0; i < data_size; i++)
        data[i] = sqrt(data[i]);
        
    end = clock();

    printf("data: %f, %f, %f, %f, %f\n", data[0], data[1], data[2], data[3], data[4]);
    printf("Elapsed time: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(data);

    return 0;
}
