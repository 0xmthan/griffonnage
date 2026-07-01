// 2026 1 Tem 16:21
// mtaheri - ysumeral

#include <stdio.h>
#include <pthread.h>

int num;
pthread_t th1;
pthread_t th2;
pthread_mutex_t mu1;

void *test()
{
    for (int i; i < 1000000; i++)
    {
        pthread_mutex_lock(&mu1);
        num++;
        pthread_mutex_unlock(&mu1);
    }
    return (NULL);
}

int main()
{
    num = 0;
    pthread_mutex_init(&mu1, NULL);

    pthread_create(&th1, NULL, test, NULL);
    pthread_create(&th2, NULL, test, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("%d\n", num);
}