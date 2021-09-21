#include <time.h>
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 16

struct timespec sleeptime = {0, 0};
int bufferSize = BUFFER_SIZE;
int buffer[BUFFER_SIZE];
int count = 0;

pthread_t producerThread = 1, consumerThread = 2;
int pAwake = 0, cAwake = 0;
int currentProducerNumber = 1;
int errorsCount = 0;
int numbersConsumed = 0;

void* producer(void* args);
void* consumer(void* args);

void awake(pthread_t thread) {
	if (thread == producerThread){
		if (pAwake) return;
		
		pAwake = 1;
		pthread_create(&producerThread, NULL, producer, NULL);
	} else {
		if (cAwake) return;
		
		cAwake = 1;
		pthread_create(&consumerThread, NULL, consumer, NULL);
	}
}

void sleep(pthread_t thread) {
	if (thread == producerThread){
		if (!pAwake) return;
		
		pthread_cancel(producerThread);
		producerThread = -1;
		pAwake = 0;
	} else {
		if (!cAwake) return;
		
		pthread_cancel(consumerThread);
		consumerThread = -2;
		cAwake = 0;
	}
}

int check(int n) {
	if (n == 1) return 0;
	
	for (int i = 2; i < n; i++)
		if (n % i == 0) return 0;
		
	return 1;
}

void* producer(void* args) {
	while (1) {
		nanosleep(&sleeptime, NULL); // cancellation point function
		currentProducerNumber++;
		if (!check(currentProducerNumber)) continue;
		
		buffer[count] = currentProducerNumber;
		count++;
		
		if (!cAwake) awake(consumerThread);
		if (count == bufferSize) {
			sleep(producerThread);
		}
	}
}

void* consumer(void* args) {
	while (1) {
		nanosleep(&sleeptime, NULL); // cancellation point function
		
		count--;
		int value = buffer[count];
		buffer[count] = 1;
		if (!check(value)) errorsCount++;
		numbersConsumed++;
		
		if (!pAwake) awake(producerThread);
		if (count == 0) {
			sleep(consumerThread);
		}
	}
}

int main() {
	for (int i = 0; i < bufferSize; i++)
		buffer[i] = 1;
	
	awake(producerThread);
	struct timespec interval = {0, 100000000};
	
	int line = 0;
	while (1) {
		printf("[%d] Status: producer - %s, consumer - %s\n", line++, pAwake ? "Awake" : "Asleep", cAwake ? "Awake" : "Asleep");
		printf("[%d] Buffer count - %d, consumer error reports - %d\n", line++, count, errorsCount);
		printf("[%d] Producer number - %d Numbers consumed - %d\n", line++, currentProducerNumber, numbersConsumed);
		printf("[%d] producer = %d, consumer = %d\n", line++, producerThread, consumerThread);
		fflush(stdout);
		nanosleep(&interval, NULL);
	}
	
	return 0;
}