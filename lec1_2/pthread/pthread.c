#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

void *print_helloworld(void *arg)
{
    printf("Hello World!!\n");
    return 0;
}

int main()
{
    int i = 0;
    pthread_t thread_arr[NUM_THREADS];

    for(i=0; i < NUM_THREADS; i++)
        pthread_create(&thread_arr[i], NULL, print_helloworld, NULL);

    for(i=0; i < NUM_THREADS; i++)
        pthread_join(thread_arr[i], NULL);

    return 0;
}