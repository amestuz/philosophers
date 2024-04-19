#include <stdio.h>
#include <pthread.h>

void	*thread_routine(void *data)
{
	pthread_t	tid;

	tid = pthread_self();
	printf("Thread [%ld]: The heaviest burden is to exist without living.\n", tid);
	return (NULL);
}

int	main(void)
{
	pthread_t	tid1;

	pthread_create(&tid1, NULL, thread_routine, NULL);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_join(tid1, NULL);
	printf("Main: Joining first thread [%ld]\n", tid1);
	return (0);
}

//gcc -pthread main.c