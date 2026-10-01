#include <stdio.h>
#include <omp.h>

int main(void)
{ 
    #pragma omp parallel num_threads(4)                         // 4개의 스레드 생성
    {
        #pragma omp task                                        // 각 스레드는 아래의 코드을 태스크로 생성하여 task pool에 넣음
        printf("task A, execution thread num: %d \n", omp_get_thread_num());
        
        #pragma omp task                                        // 각 스레드는 아래의 코드을 태스크로 생성하여 task pool에 넣음
        printf("task B, execution thread num: %d \n", omp_get_thread_num());        
    }                                                           // 암묵적 동기화에 의해 모든 thread의 실행이 완료될 때까지 기다림

    return 0;
}
