#include <stdio.h>
#include <sys/types.h>

int main() {
	int n = 900;
	
	int forkResult = fork();
	
	if (forkResult == 0) {
		n += 1;
		printf("Hello from child [PID - %d]\n", n);
	} else {
		printf("Hello from parent [PID - %d]\n", n);
	}
	
	return 0;
}