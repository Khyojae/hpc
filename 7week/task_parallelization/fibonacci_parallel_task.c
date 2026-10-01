#include <stdio.h>
#include <omp.h>
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
    double start = 0.0;
    double end = 0.0;  

    printf("Default number of threads: %d\n", omp_get_max_threads());  // default로 설정된 스레드 수 확인
    
    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single private(i)
        for(i = 1; i < MAX; i++)
        {
            #pragma omp task
            FibNumber[i] = Fibonacci(i);
        }
    }
    	
    end = omp_get_wtime();
    	
    printf("Fibonacci numbers: ");
    	
    for(i = 0; i < MAX; i++)
        printf("%d ", FibNumber[i]);
    
    printf("\nElapsed time: %f s\n", end - start);

    return 0;
}

