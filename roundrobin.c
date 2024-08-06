#include <stdio.h>
#define MAX_PROCESS 10
struct Process {
    int pid;
    int burstTime;
    int remainingTime;
    int arrivalTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};
void roundRobinScheduling(struct Process processes[], int n, int timeQuantum) {
    int totalTime = 0;
    int i, count, remain;
    int time = 0;
    for (i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        totalTime += processes[i].burstTime;
    }
    while (time < totalTime) {
        for (i = 0, count = 0; i < n; i++) {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= time) {
                if (processes[i].remainingTime > timeQuantum) {
                    time += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                }
                else {
                    time += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                }      
                if (processes[i].remainingTime == 0) {
                    processes[i].completionTime = time;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                }
            }
            else {
                count++;
            }
        }
        if (count == n) {
            break;
        }
    }
}
int main() {
    int i, n, timeQuantum;
    struct Process processes[MAX_PROCESS];
    float avgWaitingTime = 0;
    float avgTurnaroundTime = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);
    for (i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i;
    }
    roundRobinScheduling(processes, n, timeQuantum);
    for (i = 0; i < n; i++) {
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid+1, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    return 0;
}
