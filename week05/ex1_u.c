// unsyncronized version (message from thread can go before creation message)
#include <pthread.h>
#include <stdio.h>

#define THREAD_COUNT 8

void* worker(void* args) {
	int argument = *((int*)args);
	
	printf("Message from the thread %d\n", argument);
}

int main() {
	int n = THREAD_COUNT; // threads count
	pthread_t threads[THREAD_COUNT]; // threads
	int arguments[THREAD_COUNT];
	
	for (int i = 0; i < n; i++) {
		pthread_t thread;
		threads[i] = thread;
		arguments[i] = i;
		if (pthread_create(&threads[i], NULL, worker, &arguments[i]) == 0)
			printf("The thread %d has been created\n", i);
	}
	
	for (int i = 0; i < n; i++) {
		pthread_join(threads[i], NULL);
		printf("The thread %d has been terminated\n", i);
	}
	
	return 0;
}