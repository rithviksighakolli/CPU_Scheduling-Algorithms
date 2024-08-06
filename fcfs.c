#include <stdio.h>
struct process{
    int arr;
    int bst;
};
int main()
{
    int n; int t = 0;
    printf("Enter the no. of process: ");
    scanf("%d", &n);
    struct process P[n];
    for(int i = 0; i < n; i++){
        printf("Enter the arrival time of process %d: ", i+1);
        scanf("%d", &P[i].arr);
        printf("Enter the burst time of process %d: ", i+1);
        scanf("%d", &P[i].bst);
    }
    int waitingTime[n], turnAroundTime[n], completionTime[n];
    waitingTime[0] = 0;
    t = P[0].bst;
    for (int i = 1; i < n; i++) {
        if(P[i].arr > t){
            waitingTime[i] = 0;
            t += P[i].bst + (P[i].arr - t);
            }
        else{
            waitingTime[i] = t - P[i].arr;
            t += P[i].bst;
            }
    }
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = P[i].bst + waitingTime[i];
    }
    for (int i = 0; i < n; i++) {
        completionTime[i] = turnAroundTime[i] + P[i].arr;
    }
    printf("Process ID\tCompletion Time\tWaiting Time\tTurnaround Time\tArrival Time\tBurst Time\n");
    int total_waitingTime = 0, total_turnAroundTime = 0;
    for (int i = 0; i < n; i++) {
        total_waitingTime += waitingTime[i];
        total_turnAroundTime += turnAroundTime[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, completionTime[i], waitingTime[i], turnAroundTime[i], P[i].arr, P[i].bst);
    }
    printf("\nAverage waiting time = %f\n", (float)total_waitingTime / n);
    printf("Average turnaround time = %f\n", (float)total_turnAroundTime / n);
    return 0;
}
