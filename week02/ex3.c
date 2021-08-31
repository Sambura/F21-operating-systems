#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Wrong number of command line arguments. Terminating\n");
        return 0;
    }

    int n = atoi(argv[1]);
    int indent = n - 1;
    int starsCount = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < indent; j++)
            putc(' ', stdout);
        for (int j = 0; j < starsCount; j++)
            putc('*', stdout);

        indent--;
        starsCount += 2;
        putc('\n', stdout);
    }
    return 0;
}