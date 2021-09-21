// syncronized version
#include <pthread.h>
#include <stdio.h>

#define THREAD_COUNT 8

void* worker(void* args) {
	while (*(int*)args < 0) ;
	
	printf("Message from the thread %d\n", *(int*)args);
	fflush(stdout);
}

int main() {
	int n = THREAD_COUNT; // threads count
	pthread_t threads[THREAD_COUNT]; // threads
	int arguments[THREAD_COUNT];
	
	for (int i = 0; i < n; i++) {
		pthread_t thread;
		threads[i] = thread;
		arguments[i] = -1; // suspending thread until creation message is printed
		if (pthread_create(&threads[i], NULL, worker, &arguments[i]) == 0) {
			printf("The thread %d has been created\n", i);
			fflush(stdout);
		}
		
		arguments[i] = i;
	}
	
	for (int i = 0; i < n; i++) {
		pthread_join(threads[i], NULL);
		printf("The thread %d has been terminated\n", i);
	}
	
	return 0;
}