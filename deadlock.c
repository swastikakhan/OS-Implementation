#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int processes, resources;
int *available;
int **allocation;
int **request;
bool *finish;

bool is_deadlocked() {
    int *work = (int *)malloc(resources * sizeof(int));
    memcpy(work, available, resources * sizeof(int));
    memset(finish, false, processes * sizeof(bool));

    bool progress;
    do {
        progress = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    } while (progress);

    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            free(work);
            return true;
        }
    }
    free(work);
    return false;
}

void find_minimal_deadlock_breaking_set() {
    if (!is_deadlocked()) {
        printf("No deadlock detected.\n");
        return;
    }

    printf("Deadlock detected. Terminate processes: ");
    for (int i = 0; i < processes; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
        }
    }
    printf("\n");
}

int main() {
    printf("Enter total number of distinct resources: ");
    scanf("%d", &resources);
    
    available = (int *)malloc(resources * sizeof(int));
    printf("Enter number of instances for each resource type: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    
    allocation = (int **)malloc(processes * sizeof(int *));
    request = (int **)malloc(processes * sizeof(int *));
    finish = (bool *)malloc(processes * sizeof(bool));
    
    for (int i = 0; i < processes; i++) {
        allocation[i] = (int *)malloc(resources * sizeof(int));
        request[i] = (int *)malloc(resources * sizeof(int));
    }

    printf("Enter allocation matrix (%d x %d):\n", processes, resources);
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter request matrix (%d x %d):\n", processes, resources);
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    find_minimal_deadlock_breaking_set();
    
  
    free(available);
    for (int i = 0; i < processes; i++) {
        free(allocation[i]);
        free(request[i]);
    }
    free(allocation);
    free(request);
    free(finish);
    
    return 0;
}