#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    char buffer[256];

    printf("Enter the first number\n");
    fgets(buffer, 256, stdin);
    int a = atoi(buffer);

    printf("Enter the second number\n");
    fgets(buffer, 256, stdin);
    int b = atoi(buffer);

    printf("Before swap: a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("After swap: a = %d, b = %d\n", a, b);

    return 0;
}