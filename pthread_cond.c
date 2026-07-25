#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_cond_t  cond_ping;
pthread_cond_t  cond_pong;
int turn = 0; // 0 = ping's turn, 1 = pong's turn

void *ping(void *arg)
{
	int i = 0;

	while (i < 5)
	{
		pthread_mutex_lock(&mutex);
		while (turn != 0)
			pthread_cond_wait(&cond_ping, &mutex);
		printf("ping\n");
		turn = 1;
		pthread_cond_signal(&cond_pong);
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

void *pong(void *arg)
{
	int i = 0;

	while (i < 5)
	{
		pthread_mutex_lock(&mutex);
		while (turn != 1)
			pthread_cond_wait(&cond_pong, &mutex);
		printf("pong\n");
		turn = 0;
		pthread_cond_signal(&cond_ping);
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1, t2;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_ping, NULL);
	pthread_cond_init(&cond_pong, NULL);

	pthread_create(&t1, NULL, ping, NULL);
	pthread_create(&t2, NULL, pong, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_ping);
	pthread_cond_destroy(&cond_pong);
	return (0);
}
