#include <stdio.h>

int main(void) {
    printf("Please input some string with up to %d characters:\n", 256 - 1);
    char buffer[256];
    fgets(&buffer, 256, stdin);
    printf("Here is the reversed string:\n");
    int strLength = strlen(buffer) - 1;
    for (int i = strLength - 1; i >= 0; i--)
        putc(buffer[i], stdout);
    return 0;
}