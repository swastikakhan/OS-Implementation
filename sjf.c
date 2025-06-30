#include <stdio.h>

typedef struct {
    char pid[5];   
    int arrival;   
    int burst;    
    int waiting;   
    int turnaround; 
} Process;

void sortProcesses(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival || 
                (p[j].arrival == p[j + 1].arrival && p[j].burst > p[j + 1].burst)) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sjfScheduling(Process p[], int n) {
    int completed = 0, currentTime = 0;
    int isCompleted[n];
    for (int i = 0; i < n; i++) isCompleted[i] = 0;
    
    printf("\nGantt Chart:\n");
    while (completed < n) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (!isCompleted[i] && p[i].arrival <= currentTime) {
                if (shortest == -1 || p[i].burst < p[shortest].burst) {
                    shortest = i;
                }
            }
        }
        
        if (shortest == -1) {
            currentTime++;
        } else {
            printf("%s (%d-%d) | ", p[shortest].pid, currentTime, currentTime + p[shortest].burst);
            p[shortest].waiting = currentTime - p[shortest].arrival;
            p[shortest].turnaround = p[shortest].waiting + p[shortest].burst;
            currentTime += p[shortest].burst;
            isCompleted[shortest] = 1;
            completed++;
        }
    }
    printf("\n");
}

void displayResults(Process p[], int n) {
    float totalWaiting = 0, totalTurnaround = 0;
    
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
        printf("%s\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }
    
    printf("\nAverage Waiting Time: %.2f", totalWaiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaround / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];
    
    printf("Enter Process ID, Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }
    
    sortProcesses(p, n);
    sjfScheduling(p, n);
    displayResults(p, n);
    
    return 0;
}