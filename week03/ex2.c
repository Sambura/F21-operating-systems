#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 256
#define DEFAULT_ARRAY_SIZE 8

void bubble_sort(int* array, int arraySize, int (*comparator)(int, int));
void swap(int* a, int* b);
void print_array(int* array, int arraySize);
int read_array(int** arrayRef);

void bubble_sort(int* array, int arraySize, int (*comparator)(int, int)) {
	if (arraySize == 0) return;

	for (int i = 0; i < arraySize - 1; i++) {
		for (int j = 1; j < arraySize - i; j++) {
			if (!comparator(array[j - 1], array[j]))
				swap(&array[j], &array[j - 1]);
		}
	}
}
void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}
void print_array(int* array, int arraySize) {
	if (arraySize < 1) {
		printf("[ ]\n");
		return;
	}

	printf("[ %d", *array);
	for (int i = 1; i < arraySize; i++) {
		printf(", %d", array[i]);
	}
	printf(" ]\n");
}
int read_array(int** arrayRef) {
	printf("\
Input an array of integer numbers (one number per line)\n\
Type in a full stop (.) when you are finished\n"
	);
	char buffer[BUFFER_SIZE], *status;
	int arraySize = DEFAULT_ARRAY_SIZE;
	int elementsCount = 0;
	int* array = (int*)malloc(arraySize * sizeof(int));

	while (1) {
		status = fgets(buffer, BUFFER_SIZE, stdin);

		if (status == NULL) {
			printf("An error occured while inputing this one. Please try again\n");
			continue;
		}

		if (buffer[0] == '.') break;

		int number = atoi(buffer);
		if (elementsCount >= arraySize) {
			arraySize *= 2;
			int* newArray = (int*)malloc(arraySize * sizeof(int));
			for (int i = 0; i < elementsCount; i++)
				newArray[i] = array[i];
			free(array);
			array = newArray;
		}

		array[elementsCount] = number;
		elementsCount++;
	}

	*arrayRef = array;
	return elementsCount;
}

int less_than(int left, int right) {
	return left < right;
}
int greater_than(int left, int right) {
	return left > right;
}
int even_odd(int left, int right) {
	return (left % 2 == right % 2) || right % 2;
}

struct SortingInfo {
	int (*copmarator) (int, int);
	const char* name;
};

#define AscendingOrderSortingInfo {less_than, "Ascending order"};
#define DescendingOrderSortingInfo {greater_than, "Descending order"};
#define EvenOddOrderSortingInfo {even_odd, "Even-odd order"};

int main(void) {
	int* array;
	int elementsCount = read_array(&array);
	struct SortingInfo sortingInfo = AscendingOrderSortingInfo;

	printf("%d numbers were entered:\n", elementsCount);
	print_array(array, elementsCount);

	bubble_sort(array, elementsCount, sortingInfo.copmarator);

	printf("Sorted array [bubble sort, %s]:\n", sortingInfo.name);
	print_array(array, elementsCount);

	return 0;
}