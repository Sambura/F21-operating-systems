#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	DIR* dirp = opendir("/");
	if (dirp == NULL) {
		printf("Error: couldn't access root");
		return -1;
	}
	
	int index = 0;
	
	struct dirent* dp;
	while ((dp = readdir(dirp)) != NULL) {
		// remove current and parent directories from consideration
		if (strcmp(dp->d_name, ".") == 0) continue;
		if (strcmp(dp->d_name, "..") == 0) continue;
		
		printf("%s\n", dp->d_name);
	}

	return 0;
}