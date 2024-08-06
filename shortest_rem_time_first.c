#include <stdio.h>
#include <limits.h>
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n], arrival_time[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1;
    }
    int wt[n], tat[n], ct[n], total_wt = 0, total_tat = 0;
    int complete = 0, t = 0;
    int remaining[n];
    for (int i = 0; i < n; i++)
        remaining[i] = burst_time[i];
    while (complete != n) {
        int shortest = -1;
        int min_remaining = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (arrival_time[j] <= t && remaining[j] < min_remaining && remaining[j] > 0) {
                min_remaining = remaining[j];
                shortest = j;
            }
        }
        if (shortest == -1) {
            t++;
            continue;
        }
        remaining[shortest]--;
        if (remaining[shortest] == 0) {
            complete++;
            ct[shortest] = t + 1;
            wt[shortest] = ct[shortest] - burst_time[shortest] - arrival_time[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
            tat[shortest] = burst_time[shortest] + wt[shortest];
            total_wt += wt[shortest];
            total_tat += tat[shortest];
        }
        t++;
    }
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
  
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrival_time[i], burst_time[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage waiting time: %.2f", (float)total_wt/n);
    printf("\nAverage turnaround time: %.2f\n", (float)total_tat/n);
  
    return 0;
}
