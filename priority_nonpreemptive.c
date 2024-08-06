#include<stdio.h>
#include<stdlib.h>
struct Process {
    int pid;
    int priority;
    int arrival_time;
    int burst_time;
};
void swap(struct Process *x, struct Process *y)
{
    struct Process temp = *x;
    *x = *y;
    *y = temp;
}
void sort_processes(struct Process *processes, int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority ||
               (processes[i].priority == processes[j].priority &&
                processes[i].burst_time > processes[j].burst_time)) {
                swap(&processes[i], &processes[j]);
            }
        }
    }
}
void tatwt(int *ct, struct Process *processes, int *tat, int *wt, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - processes[i].arrival_time;
        wt[i] = tat[i] - processes[i].burst_time;
    }
}
int main()
{
    int i, n;
    float awt = 0, atat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));
    int *ct = (int *)malloc(n * sizeof(int));
    int *tat = (int *)malloc(n * sizeof(int));
    int *wt = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
	    printf("Enter the process id: ");
        scanf("%d", &processes[i].pid);
        printf("Enter the arrival time of the process: ");
        scanf("%d",&processes[i].arrival_time);
        printf("Enter the burst time of the process: ");
        scanf("%d", &processes[i].burst_time);
        printf("Enter the priority of the process: ");
        scanf("%d", &processes[i].priority);
    }
    sort_processes(processes, n);
    ct[0] = processes[0].arrival_time + processes[0].burst_time;
    for (i = 1; i < n; i++) {
        int shortest_job = i;
        for (int j = i; j < n; j++) {
            if (processes[j].arrival_time <= ct[i - 1] && processes[j].priority == processes[i].priority) {
                if (processes[j].burst_time < processes[shortest_job].burst_time) {
                    shortest_job = j;
                }
            }
        }
        swap(&processes[i], &processes[shortest_job]);
        ct[i] = ct[i - 1] + processes[i].burst_time;
    }
    tatwt(ct, processes, tat, wt, n);
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, ct[i], tat[i], wt[i]);
        awt += wt[i];
        atat += tat[i];
    }
    printf("\nAverage turn around time: %f\nAverage waiting time: %f\n", atat / n, awt / n);
    return 0;
}
