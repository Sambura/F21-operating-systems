#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	for (int i = 0; i < 45; i++) {
		// printf("Iteration #%d / 45 \n", i + 1);
		int size = 300 * 1024 * 1024;
		char* a = malloc(size);
		memset(a, 0, size);
		sleep(1);
	}
	
	// Note: all my excercises were done using WSL2
	// 
	// ex2 comments:
	//
	// as the process executes, the amount of free memory
	// gradually decreases until it reaches about 100 Mb
	// 
	// as soon as there is less then 100 Mb of free memory, 
	// the memory manager starts performing a lot of swapouts
	// (about 3 Gb total in my case)
	//
	// at some point (is my case - after 40 loop iterations)
	// memory manager kills the process, without waiting 
	// for it to finish
	
	// ex3 comments:
	//
	// as the process executes, it occupies more and more memory
	// when percentage of occupied memory exceeded ~93%
	// CPU usage increased from ~10% to ~100%
	// Probably this is due to work of memory manager
	
	return (0);
}
