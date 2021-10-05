#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

int main()
{
    char buffer[BUFFER_SIZE];

    printf("Enter the size of the array to be allocated: \n");

    fgets(buffer, BUFFER_SIZE, stdin);
    int n = atoi(buffer);

    if (n <= 0) {
        printf("Empty or negative sized array requested. Terminating\n");
        return 0;
    }

    int* array = (int*) malloc(sizeof(int) * n);
    if (array == NULL) {
        printf("Malloc fault. Terminating\n");
        return -1;
    }

    for (int i = 0; i < n; i++)
        array[i] = i;

    printf("%d", array[0]);
    for (int i = 1; i < n; i++)
        printf(", %d", array[i]);
	printf("\n");

    free(array);

    return 0;
}