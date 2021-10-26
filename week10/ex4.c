#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* dirPath = "tmp/";

struct FileInfo {
	char* name;
	ino_t iNode;
	int hardLinkCount;
};

int main() {
	DIR* dirp = opendir(dirPath);
	if (dirp == NULL) {
		printf("Error: couldn't open a folder");
		return -1;
	}
	
	struct FileInfo fileInfos[64]; // static array for simplicity
	int index = 0;
	
	struct dirent* dp;
	while ((dp = readdir(dirp)) != NULL) {
		// remove current and parent directories from consideration
		if (strcmp(dp->d_name, ".") == 0) continue;
		if (strcmp(dp->d_name, "..") == 0) continue;
		
		fileInfos[index].name = dp->d_name;
		fileInfos[index].iNode = dp->d_ino;
		fileInfos[index].hardLinkCount = 0;
		index++;
	}
	
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++)
			if (fileInfos[i].iNode == fileInfos[j].iNode) {
				fileInfos[i].hardLinkCount++;
			}
	}
	
	for (int i = 0; i < index; i++) {
		if (fileInfos[i].hardLinkCount < 2) continue;
		printf("%s - %s", fileInfos[i].name, fileInfos[i].name);
		
		for (int j = 0; j < index; j++) {
			if (i != j && fileInfos[j].iNode == fileInfos[i].iNode)
				printf(", %s", fileInfos[j].name);
		}
		
		printf("\n");
	}

	return 0;
}