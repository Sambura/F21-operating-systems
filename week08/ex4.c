#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
	printf("| current RAM usage |\n");
	printf("|-------------------|\n");
	
	struct rusage r_usage;
	
	for (int i = 0; i < 30; i++) {
		int size = 10 * 1024 * 1024;
		char* a = malloc(size);
		memset(a, 0, size);
		getrusage(RUSAGE_SELF, &r_usage);
		printf("| %14ld Kb |\n", r_usage.ru_maxrss);
		sleep(1);
	}
}