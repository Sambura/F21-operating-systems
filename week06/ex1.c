#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

const char* FilePath = "input.csv";

struct ProcessInfo {
    int arrivalTime;
    int burstTime;
};

int checkDigit(char c) {
    return c >= '0' && c <= '9';
}

struct ProcessInfo processes[10];
int count = 0;

void ParseCSV() {
    FILE* fp;

    fp = fopen(FilePath, "r");
    while (1) {
        int at, bt;
        char c;
        if (fscanf(fp, "%d,%d%c", &at, &bt, &c) < 2) break;
        processes[count++] = (struct ProcessInfo ){ at, bt };
        if (c != '\n') break;
    }

    fclose(fp);
}

int comparer(void* a, void* b) {
    int f = ((struct ProcessInfo*)a)->arrivalTime;
    int s = ((struct ProcessInfo*)b)->arrivalTime;
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main()
{
    ParseCSV();
    qsort(processes, count, sizeof(struct ProcessInfo), comparer);

    printf("#P     AT     BT     CT     TAT    WT\n\n");

    float atat = 0;
    float awt = 0;
    int currentTime = 0;
    for (int i = 0; i < count; i++) {
        int at = processes[i].arrivalTime;
        int bt = processes[i].burstTime;
        if (currentTime < at)
            currentTime = at;
        int ct = currentTime + processes[i].burstTime;
        int tat = ct - at;
        int wt = tat - bt;
        printf("P%-6d%-7d%-7d%-7d%-7d%-7d\n", i + 1, at, bt, ct, tat, wt);
        currentTime = ct;
        atat += tat;
        awt += wt;
    }

    printf("\nAverage turnaround time: %.2f\n", atat / count);
    printf("Average waiting time: %.2f\n", awt / count);

    return 0;
}