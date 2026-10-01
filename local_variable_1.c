#include<stdio.h>
#include<omp.h>
intmain()
{
int x = 0;
printf("main area x : %d\n", x);
#pragma ompparallel num_threads(4) private(x) // 스레드내의로컬변수생성
{
if(omp_get_thread_num() == 0)
x = 1;
else if(omp_get_thread_num() == 1)
x = 2;
else if(omp_get_thread_num() == 2)
x = 3;
else if(omp_get_thread_num() == 3)
x = 4;
printf("Num %d thread area x : %d\n", omp_get_thread_num(), x);
}
printf("main area x : %d\n", x);

return 0;
}
