#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// name of the function is changed to avoid name collision
void* _realloc(void* ptr, size_t size) {
	if (ptr == NULL) { // if original block does not exist
		if (size <= 0) { // if size is non-positive
			return NULL;
		}

		return malloc(size); // if size is nonzero
	} 

	if (size <= 0) { // if original block does exist, but new size is non-positive
		free(ptr); // free memory
		return malloc(1); // return pointer to the new "minimum sized object"
	}

	// if original block does exist and new size is reasanoble
	// create new block
	// copy data
	// free old block
	void* newBlock = malloc(size);
	memcpy(newBlock, ptr, size);
	free(ptr);
	return newBlock;
}

int main() {
	int* a = NULL;
	printf("a* is a null pointer now: a = %p\n", a);

	a = _realloc(a, 10 * sizeof(int));
	for (int i = 0; i < 10; i++) a[i] = i;
	printf("a* after calling realloc(a, 10): a = %p\n", a);
	printf("a's contents:\n");
	for (int i = 0; i < 10; i++) printf("%d ", a[i]);
	printf("\n\n");

	a = _realloc(a, 15 * sizeof(int));
	for (int i = 10; i < 15; i++) a[i] = 0;
	printf("a* after calling realloc(a, 15): a = %p\n", a);
	printf("a's contents:\n");
	for (int i = 0; i < 15; i++) printf("%d ", a[i]);
	printf("\n\nNote, that the last 5 elements were set to zero manually to show, that program has an access to the new memory\n\n");
	//
	a = _realloc(a, 5 * sizeof(int));
	printf("a* after calling realloc(a, 5): a = %p\n", a);
	printf("a's contents:\n");
	for (int i = 0; i < 5; i++) printf("%d ", a[i]);
	printf("\n\n");
	//
	a = _realloc(a, 0);
	printf("a* after calling realloc(a, 0): a = %p\n", a);
	printf("a should point to the memory block of size 1 byte now (minimum sized object)\n");
	printf("note: the address may be the same, but block size is different\n\n");

	return 0;
}
