#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <omp.h>

int min(int a, int b)
{
    if(a < b)
        return a;
    else if(a > b)
        return b;
    else
        return a;
}

int max(int a, int b)
{
    if(a > b)
        return a;
    else if(a < b)
        return b;
    else
        return a;
}

int get_min(int length, int iters, int **gArray)
{
    int i, j;
    int myMin = INT_MAX;            // INT_MAX (maximum value for integer type):  2147483647
        
    for(i = 0; i < length; i++)
        for (j = 0; j < iters; j++)
            myMin = min(myMin, gArray[i][j]);

    return myMin;
}

int get_max(int length, int iters, int **gArray)
{
    int i, j;
    int myMax = INT_MIN;            // INT_MIN (mininum value for integer type): -2147483648
        
    for(i = 0; i < length; i++)
        for (j = 0; j < iters; j++)
            myMax = max(myMax, gArray[i][j]);

    return myMax;
}

long get_sum(int length, int iters, int **gArray)
{
    int i, j;
    long mySum = 0;            // INT_MIN (mininum value for integer type): -2147483648
        
    for(i = 0; i < length; i++)
        for (j = 0; j < iters; j++)
            mySum = mySum + gArray[i][j];

    return mySum;
}

int main(int argc, char *argv[])
{
    int length = 1000000, iters = 100;
    int i, j;
    int **gArray;
    int myMin = INT_MAX;            // INT_MAX (maximum value for integer type):  2147483647
    int myMax = INT_MIN;            // INT_MIN (mininum value for integer type): -2147483648
    long mySum = 0;
    double t1, t2;
    
    gArray = (int**)malloc(length * sizeof(int*));

    for (i = 0; i < length; i++)
        gArray[i] = (int*)malloc(iters * sizeof(int));

    srand(0);

    for (i = 0; i < length; i++)
        for (j = 0; j < iters; j++)
            gArray[i][j] = rand();    

    t1 = omp_get_wtime();

    #pragma omp parallel sections num_threads(3){
    #pragma omp parallel section{ //myMin 계산
        get_min(length,iters,gArray);
        }

    #pragma omp parallel section{ //myMax 계산
        get_max(length,iters,gArray);
    }

     #pragma omp parallel section{ //mySum 계산
   get_sum(length,iters,gArray)
    }

    }

    t2 = omp_get_wtime(); 
    
    printf("min: %d, max: %d, total: %ld, elapsed time: %6.3f (sec) \n", myMin, myMax, mySum, t2 - t1);
   
    return 0;
}

