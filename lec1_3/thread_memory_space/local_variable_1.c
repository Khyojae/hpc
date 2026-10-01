#include <stdio.h>
#include <omp.h>

int main()
{
    int x = 0;

    printf("main area x : %d\n", x);

    #pragma omp parallel num_threads(4) private(x)                     // 스레드 내의 로컬 변수 생성
    {
        if (omp_get_thread_num() == 0)
            x = 1;
        else if (omp_get_thread_num() == 1)
            x = 2;
        else if (omp_get_thread_num() == 2)
            x = 3;
        else if (omp_get_thread_num() == 3)
            x = 4;

        printf("Num %d thread area x : %d\n", omp_get_thread_num(), x);
    }

    printf("main area x : %d\n", x);

    return 0;
}
