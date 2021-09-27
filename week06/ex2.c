#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

const char* FilePath = "input.csv";

struct ProcessInfo {
    int arrivalTime;
    int burstTime;
};

int checkDigit(char c) {
    return c >= '0' && c <= '9';
}

struct ProcessInfo processes[10];
int done[10];
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

void print(char c, int count) {
    for (int i = 0; i < count; i++) {
        putc(c, stdout);
    }
}

int main()
{
    ParseCSV();
    for (int i = 0; i < 10; i++) done[i] = 0;

    printf("#P     AT     BT     CT     TAT    WT\n\n");

    float atat = 0;
    float awt = 0;
    int currentTime = 0;
    for (int i = 0; i < count; i++) {
        int currentProcess = -1;
        int bestBT = INT_MAX;

        for (int j = 0; j < count; j++) { // pick the process that already arrived
            if (done[j]) continue;
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < bestBT) {
                currentProcess = j;
                bestBT = processes[j].burstTime;
            }
        }

        if (currentProcess < 0) { // if no processes arrived yet, pick the process with the least arrive time (preferably pick shortest burst time)
            int bestAT = INT_MAX;
            bestBT = INT_MAX;
            for (int j = 0; j < count; j++) {
                if (done[j]) continue;
                if (bestAT > processes[j].arrivalTime) {
                    currentProcess = j;
                    bestAT = processes[j].arrivalTime;
                    bestBT = processes[j].burstTime;
                }
                else if (bestAT == processes[j].arrivalTime && bestBT > processes[j].burstTime) {
                    currentProcess = j;
                    bestAT = processes[j].arrivalTime;
                    bestBT = processes[j].burstTime;
                }
            }
        }

        done[currentProcess] = 1;
        int at = processes[currentProcess].arrivalTime;
        int bt = processes[currentProcess].burstTime;
        if (currentTime < at)
            currentTime = at;
        int ct = currentTime + bt;
        int tat = ct - at;
        int wt = tat - bt;
        printf("P%-6d%-7d%-7d%-7d%-7d%-7d\n", i + 1, at, bt, ct, tat, wt);
        currentTime = ct;
        atat += tat;
        awt += wt;
    }

    printf("\nAverage turnaround time: %.2f\n", atat / count);
    printf("Average waiting time: %.2f\n", awt / count);

    //////////////////////////////////////////////////////////////////////

    // uncomment to get time graph of the processes
    /*
    for (int i = 0; i < 10; i++) done[i] = 0;
    printf("\n");
    int waitingTimes[256];
    for (int i = 0; i < 256; i++) waitingTimes[i] = 0;

    currentTime = 0;
    for (int i = 0; i < count; i++) {
        int currentProcess = -1;
        int bestBT = INT_MAX;

        for (int j = 0; j < count; j++) { // pick the process that already arrived
            if (done[j]) continue;
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < bestBT) {
                currentProcess = j;
                bestBT = processes[j].burstTime;
            }
        }

        if (currentProcess < 0) { // if no processes arrived yet, pick the process with the least arrive time (preferably pick shortest burst time)
            int bestAT = INT_MAX;
            bestBT = INT_MAX;
            for (int j = 0; j < count; j++) {
                if (done[j]) continue;
                if (bestAT > processes[j].arrivalTime) {
                    currentProcess = j;
                    bestAT = processes[j].arrivalTime;
                    bestBT = processes[j].burstTime;
                }
                else if (bestAT == processes[j].arrivalTime && bestBT > processes[j].burstTime) {
                    currentProcess = j;
                    bestAT = processes[j].arrivalTime;
                    bestBT = processes[j].burstTime;
                }
            }
        }

        done[currentProcess] = 1;
        int at = processes[currentProcess].arrivalTime;
        int bt = processes[currentProcess].burstTime;
        if (currentTime < at) {
            int wait = at - currentTime;
            for (int j = currentTime; j < at; j++)
                waitingTimes[j] = 1;
            currentTime = at;
        }
        int ct = currentTime + bt;
        int tat = ct - at;
        int wt = tat - bt;
        printf("P%-15d|", i + 1);
        print(' ', currentTime - wt);
        print('_', wt);
        print('#', bt);
        printf("\n");
        currentTime = ct;
    }

    printf("Standalone time |");
    for (int i = 0; i < currentTime; i++) {
        putc(waitingTimes[i] ? '#' : '_', stdout);
    }
    printf("\n");
    */

    return 0;
}