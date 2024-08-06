#include <stdio.h>
void sjf(int bt[], int at[], int n)
{
    int wt[n], tat[n], ct[n], total_wt = 0, total_tat = 0;
    int time = 0;
    for (int i = 0; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < i; j++)
            wt[i] += bt[j];
        wt[i] -= at[i];
        if (wt[i] < 0)
            wt[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        ct[i] = time + bt[i];
        time += bt[i];
    }
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage waiting time: %.2f", (float)total_wt/n);
    printf("\nAverage turnaround time: %.2f\n", (float)total_tat/n);
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int burst_time[n], arrival_time[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
    }
    sjf(burst_time, arrival_time, n);
    return 0;
}
