#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define resourceTypeCount 3
#define processCount 5
#define iPlusOne i + 1

const char const* input = "input.txt";

int main() {
	// Data section
	int existing[resourceTypeCount];
	int available[resourceTypeCount];
	int current[processCount][resourceTypeCount];
	int requested[processCount][resourceTypeCount];
	int finalState[processCount]; // 0 - unknown / deadlocked, 1 - completed

	// File open section
	FILE* fp = fopen(input, "r");
	if (fp == NULL) {
		printf("Input file opening failed\n");
		perror("Cause ");
		return -1;
	}
	
	// file read section (full caveman style parsing)
	for (int i = 0; i < resourceTypeCount; i++) fscanf(fp, "%d", &existing[i]);
	for (int i = 0; i < resourceTypeCount; i++) fscanf(fp, "%d", &available[i]);
	for (int j = 0; j < processCount; j++) for (int i = 0; i < resourceTypeCount; i++) fscanf(fp, "%d", &current[j][i]);
	for (int j = 0; j < processCount; j++) for (int i = 0; i < resourceTypeCount; i++) fscanf(fp, "%d", &requested[j][i]);

	// initialize final state array
	for (int i = 0; i < processCount; i++) finalState[i] = 0;

	int iterationsLeft = processCount;
	for (int i = 0; iterationsLeft > 0; i = (i == processCount) ? 0 : i + 1) { // loop through until break
		iterationsLeft--;

		if (finalState[i] == 0) { // if this process is not processed yet
			printf("Analyzing proccess #%d\n", iPlusOne);
			int runnableFlag = 1;
			for (int j = 0; j < resourceTypeCount; j++) { // check, whether we have all the required resources
				runnableFlag &= requested[i][j] <= available[j];
			}

			if (runnableFlag) { // if we have the required resources for the current process, use them, and mark the proccess as terminated
				printf("Enough resources for process #%d - its state changed to 'completed'\n", iPlusOne);
				printf("Current available resources: [");
				for (int j = 0; j < resourceTypeCount; j++) {
					available[j] += current[i][j];
					printf(" %d ", available[j]);
				}
				printf("]\n");

				iterationsLeft = processCount; // set changed flag, because another process completed its execution
				finalState[i] = 1; // indicate, that the final state is 'completed'
			} else 
				printf("Not enough resources for process #%d - skipped\n", iPlusOne);
		}
	}

	printf("\nIterations complete. The result:\n\n");

	int deadlockFlag = 0;
	for (int i = 0; i < processCount; i++) {
		if (finalState[i] == 1) continue;

		deadlockFlag = 1;
		printf("Process #%d is deadlocked. ", iPlusOne);

		int exceptionFlag = 0;
		for (int j = 0; j < resourceTypeCount; j++) {
			exceptionFlag |= requested[i][j] + current[i][j] > existing[j];
		}

		if (exceptionFlag)
			printf("The proccess required more resources than there is in the system");
		printf("\n");
	}

	if (!deadlockFlag) {
		printf("No deadlocks detected\n");
	}

	return 0;
}
