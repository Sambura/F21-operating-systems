#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min(x,y) ((x) < (y) ? (x) : (y))

const char* FilePath = "input.csv";

struct ProcessInfo {
    int arrivalTime;
    int burstTime;

    int cpuTime;
    int completionTime;
};

struct ProcessInfo processes[10];
int count = 0;

void ParseCSV() {
    FILE* fp;
    
    fp = fopen(FilePath, "r");
    while (1) {
        int at, bt;
        char c;
        if (fscanf(fp, "%d,%d%c", &at, &bt, &c) < 2) break;
        processes[count++] = (struct ProcessInfo ){ at, bt, 0, 0 };
        if (c != '\n') break;
    }

    fclose(fp);
}

void print(char c, int count) {
    for (int i = 0; i < count; i++) {
        putc(c, stdout);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("The program requires one integer parameter (quantum)\n");
        return 0;
    }

    int quantum = atoi(argv[1]);
    printf("Time quantum = %d\n\n", quantum);
    ParseCSV();

    int currentProcess = -1;
    int currentTime = 0;
    int completed = 0;

    while (completed < count) {
        for (int j = currentProcess + 1, loopCount = 0; loopCount < count; j++, loopCount++) { // pick the next process that already arrived
            if (j >= count) j = 0; // loop values
            if (processes[j].completionTime > 0) continue; // completed processes
            if (processes[j].arrivalTime > currentTime) continue; // procceses that did not arrive
            currentProcess = j;
            break;
        }

        if (currentProcess < 0 || processes[currentProcess].completionTime > 0) { // if there are no uncompleted arrived processes, wait
            currentTime = INT_MAX;
            for (int i = 0; i < count; i++) {
                if (processes[i].completionTime == 0 && processes[i].arrivalTime < currentTime) {
                    currentTime = processes[i].arrivalTime;
                    currentProcess = i;
                }
            }
        }

        int maxCpu = min(quantum, processes[currentProcess].burstTime - processes[currentProcess].cpuTime);
        processes[currentProcess].cpuTime += maxCpu;
        currentTime += maxCpu;
        if (processes[currentProcess].cpuTime == processes[currentProcess].burstTime) {
            processes[currentProcess].completionTime = currentTime;
            completed++;
        }
    }

    printf("#P     AT     BT     CT     TAT    WT\n\n");
    float atat = 0;
    float awt = 0;

    for (int i = 0; i < count; i++) {
        int at = processes[i].arrivalTime;
        int bt = processes[i].burstTime;
        int ct = processes[i].completionTime;
        int tat = ct - at;
        int wt = tat - bt;
        atat += tat;
        awt += wt;

        printf("P%-6d%-7d%-7d%-7d%-7d%-7d\n", i + 1, at, bt, ct, tat, wt);
    }

    printf("\nAverage turnaround time: %.2f\n", atat / count);
    printf("Average waiting time: %.2f\n", awt / count);

    return 0;
}