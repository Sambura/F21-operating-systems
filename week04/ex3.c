#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 256

void type_prompt() {
	printf("> ");
}

void read_command(char* buffer, int bufferSize) {
	fgets(buffer, bufferSize, stdin);
}

int execute_command(char* command) {
	if (strcmp(command, "!exit\n") == 0) return -1;
	system(command);
	
	return 0;
}

int main() {
	char buffer[BUFFER_SIZE];
	
	while (1) {
		type_prompt();
		read_command(buffer, BUFFER_SIZE);
		if (execute_command(buffer) < 0) break;
	}
	
	return 0;
}