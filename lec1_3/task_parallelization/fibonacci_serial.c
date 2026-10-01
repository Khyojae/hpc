#include <stdio.h>
#include <time.h>
#define MAX 41

int Fibonacci(int n)                            // 피보나치 수열을 구하는 재귀함수
{
    int x, y;

    if(n < 2) 
        return n;
    else
    {
        x = Fibonacci(n - 1);
        y = Fibonacci(n - 2);
        return (x+y);
    }
}

int main()
{
    int FibNumber[MAX] = {0};
    int i = 0;
    clock_t before;
    double  result;	
    
    before = clock();

    for(i = 1; i < MAX; i++)
    {
        FibNumber[i] = Fibonacci(i);
    }
    	
    result = (double)(clock() - before) / CLOCKS_PER_SEC;
    	
    printf("Fibonacci numbers: ");
    	
    for(i = 0; i < MAX; i++)
        printf("%d ", FibNumber[i]);

    printf("\nElapsed time: %f s\n", result);

    return 0;
}

