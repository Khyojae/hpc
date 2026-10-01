#include <stdio.h>
#include <omp.h>

int main(void)
{
    int i = 0;

    #pragma omp parallel num_threads(4)                                // 4개의 스레드 생성
    {
        #pragma omp single                                             // 스레드 중 하나의 스레드만 실행됨(마스터 스레드가 아닐 수 있음)
        {
            while (i < 10)
            {
                #pragma omp task                                        // 스레드 중 하나의 스레드가 태스크들을 생성하여 task pool에 넣음
                printf("index: %d, thread num: %d \n", i, omp_get_thread_num());

                i = i + 1;
            }
        }                                                               // 암묵적 동기화에 의해 모든 thread의 실행이 완료될 때까지 기다림
    }

    return 0;
}