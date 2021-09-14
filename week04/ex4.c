#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 256
#define INITIAL_ARRAY_SIZE 8

char* DefaultEnvironment[] = { NULL };
const char* PathPrefix = "/usr/bin/";

void* malloc(size_t size);
void free(void *ptr);

void type_prompt() {
	printf("> ");
}

void read_command(char* buffer, int bufferSize) {
	fgets(buffer, bufferSize, stdin);
}

int execute_command(char* command) {
	if (strcmp(command, "!exit\n") == 0) return -1;
	
	int argvSize = INITIAL_ARRAY_SIZE;
	int argvCount = 0;
	char** argv = (char**) malloc(argvSize * sizeof(char*));
	
	int startIndex = 0;
	
	for (int i = 0; ; i++) {
		if (command[i] == ' ' || command[i] == '\n' || command[i] == '\0') {
			int strSize = (i - startIndex + 1) * sizeof(char);
			argv[argvCount] = (char*) malloc(strSize);
			memcpy(argv[argvCount], command + startIndex, strSize - 1);
			argv[argvCount][strSize - 1] = '\0';
			argvCount++;
			startIndex = i + 1;
			// extend array
			if (argvCount == argvSize) {
				int newArgvSize = argvSize * 2;
				char** copy = (char**) malloc(newArgvSize * sizeof(char*));
				memcpy(copy, argv, argvSize * sizeof(char));
				free(argv);
				argv = copy;
				argvSize = newArgvSize;
			}
		}
		
		if (command[i] == '\n' || command[i] == '\0') {
			argv[argvCount] = NULL;
			break;
		}
	}
	
	int isBackground = strcmp(argv[argvCount - 1], "&") == 0;
	if (isBackground) {
		argvCount--;
		free(argv[argvCount]);
		argv[argvCount] = NULL;
	}
	
	int pathnameLength = strlen(argv[0]);
	int pathPrefixLength = strlen(PathPrefix);
	char* pathname = (char*) malloc((pathnameLength + pathPrefixLength + 1) * sizeof(char));
	memcpy(pathname, PathPrefix, pathPrefixLength);
	memcpy(pathname + pathPrefixLength, argv[0], pathnameLength + 1);

	pid_t pid = fork();
	if (pid == 0) {
		execve(pathname, argv, DefaultEnvironment);
		printf("Error: execve failed\n");
		return -1;
	}
	
	if (isBackground) {
		printf("Running %s in background\n", pathname);
	} else {
		waitpid(pid, NULL, 0);
	}
	
	free(pathname);
	for (int i = 0; i < argvCount; i++)
		free(argv[i]);
	free(argv);

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