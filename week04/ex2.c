#include <stdio.h>
#include <sys/types.h>

int main() {
	
	for (int i = 0; i < 5; i++) { // creates 2^5 processes
		fork();
		
		sleep(5);
	}
	
	return 0;
}