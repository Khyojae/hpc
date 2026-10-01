#include <stdio.h>
#include <omp.h>

int main() 
{
    int sum = 0, i = 0;
    int data[1000] = {0};

    for(i = 0; i < 1000; i++)
        data[i] = i + 1;

    #pragma omp parallel for reduction(+:sum)
    for(i = 0; i < 1000; i++)
        sum += data[i];

    printf("sum = %d\n", sum);
    return 0;
}
