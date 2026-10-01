#include <stdio.h>
#include <omp.h>
int main(void)
{
int a = 0;
printf("Serial Area a =  %d\n", a);
omp_set_num_threads(4);                    
#pragma omp parallel shared(a)
{
if(omp_get_thread_num() == 0)
a = 1;
else if(omp_get_thread_num() == 1)
a = 2;
else if(omp_get_thread_num() == 2)
a = 3;
else if(omp_get_thread_num() == 3)
a = 4;
else
a = 10;
// parallel 지시어 영역(병렬 영역)에서생성되는스레드수설정
printf("%d Thread Area a = %d \n", omp_get_thread_num(), a); 
}
printf("Serial Area a =  %d\n", a);
return 0;
}