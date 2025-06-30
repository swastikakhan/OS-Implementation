#include <stdio.h>

typedef struct {
    int pid;       
    int arrival;   
    int burst;     
    int remaining; 
    int waiting;   
    int turnaround; 
} Process;

void roundRobinScheduling(Process p[], int n, int quantum) {
    int completed = 0, currentTime = 0;
    printf("\nGantt Chart:\n");
    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                done = 0;
                printf("[P%d] ", p[i].pid);
                if (p[i].remaining > quantum) {
                    currentTime += quantum;
                    p[i].remaining -= quantum;
                } else {
                    currentTime += p[i].remaining;
                    p[i].waiting = currentTime - p[i].arrival - p[i].burst;
                    p[i].turnaround = currentTime - p[i].arrival;
                    p[i].remaining = 0;
                    completed++;
                }
            }
        }
        if (done) break;
    }
    printf("\n");
}

void displayResults(Process p[], int n) {
    float totalWaiting = 0, totalTurnaround = 0;
    
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }
    
    printf("\nAverage Waiting Time: %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }
    
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
    roundRobinScheduling(p, n, quantum);
    displayResults(p, n);
    
    return 0;
}
