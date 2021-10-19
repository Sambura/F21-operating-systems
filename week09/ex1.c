#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char* inputFilePath = "input.txt";

struct Page {
	int id;
	uint16_t age;
};

void updatePageAge(struct Page* page, int r) {
	page->age = (page->age >> 1) | (r << (sizeof(page->age) * 8 - 1));
}

int main() {
	printf("Input the number of page frames in the main memory:\n");
	
	// get input
	char buffer[32];
	fgets(buffer, 32, stdin);
	int pageCount = atoi(buffer);
	if (pageCount <= 0) {
		printf("invalid number of page frames\n");
		return 0;
	}

	// init pages
	struct Page *pages = malloc(pageCount * sizeof(struct Page));
	if (pages == NULL) {
		printf("malloc fault\n");
		return -1;
	}
	for (int i = 0; i < pageCount; i++) 
		pages[i] = (struct Page) { -1, 0 }; // id = -1 means no page

	// init input file
	FILE* fp = fopen(inputFilePath, "r");

	// init variables
	int clock = 1;
	int hit = 0;
	int miss = 0;
	int ttt = 0;

	// start paging simulation
	for (int current; fscanf(fp, "%d", &current) != EOF; clock++) {
		unsigned char referencedIndex = 0; // index of the referenced page in this cycle

		// checking hit/miss and searching for the page to replace
		for (int i = 0; i < pageCount; i++) {
			if (pages[i].id == current) { // if hit
				referencedIndex = i;
				break;
			}

			// if page is empty - certanly replace it.
			// OR if there is page with smaller age than current - replace it (empty pages always have 0 age)
			if (pages[i].id == -1 || pages[i].age < pages[referencedIndex].age) {
				referencedIndex = i;
			}
		}
		
		int isHit = pages[referencedIndex].id == current;

		hit += isHit;
		miss += !isHit;
		if (!isHit) // if this cycle is a miss, replace page
			pages[referencedIndex] = (struct Page){ current, 0 };

		for (int i = 0; i < pageCount; i++) // update age of all pages
			updatePageAge(&pages[i], i == referencedIndex);

		// print info about the state of the memory after the current cycle
		printf("Clock tick: %4d, current page id: %4d [%s]\n", clock, current, isHit ? "hit" : "miss");
		for (int i = 0; i < pageCount; i++) {
			printf("page %3d, id = %3d, age = %5d %c\n", i, pages[i].id, pages[i].age, i == referencedIndex ? '<' : '\0');
		}

		printf("\n");
	}

	// print hit/miss counts and their ratio
	printf("hit = %d miss = %d ratio = %f\n", hit, miss, (float)hit / miss);

	return 0;
}
