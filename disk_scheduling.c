
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define MAX 100

void fcfs(int requests[], int n, int head) {
    int seek_time = 0;
    printf("\nFCFS Order: %d", head);
    for (int i = 0; i < n; i++) {
        seek_time += abs(head - requests[i]);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Seek Time: %d", seek_time);
    printf("\nAverage Seek Time: %.2f\n", (float)seek_time / n);
}

void sstf(int requests[], int n, int head) {
    int seek_time = 0;
    int done[MAX] = {0};
    int count = 0;

    printf("\nSSTF Order: %d", head);

    while (count < n) {
        int min = 1e9, index = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                int dist = abs(head - requests[i]);
                if (dist < min) {
                    min = dist;
                    index = i;
                }
            }
        }

        seek_time += abs(head - requests[index]);
        head = requests[index];
        done[index] = 1;
        count++;
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d", seek_time);
    printf("\nAverage Seek Time: %.2f\n", (float)seek_time / n);
}

void scan(int requests[], int n, int head, int disk_size, char direction[]) {
    int seek_time = 0;
    int i, j;
    int sorted[MAX];

    for (i = 0; i < n; i++) {
        sorted[i] = requests[i];
    }

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (sorted[i] > sorted[j]) {
                int temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    printf("\nSCAN Order: %d", head);

    if (strcmp(direction, "up") == 0) {
        for (i = 0; i < n; i++) {
            if (sorted[i] >= head) break;
        }

        for (j = i; j < n; j++) {
            seek_time += abs(head - sorted[j]);
            head = sorted[j];
            printf(" -> %d", head);
        }

        if (head != disk_size - 1) {
            seek_time += abs(head - (disk_size - 1));
            head = disk_size - 1;
        }

        for (j = i - 1; j >= 0; j--) {
            seek_time += abs(head - sorted[j]);
            head = sorted[j];
            printf(" -> %d", head);
        }
    } else {
        for (i = n - 1; i >= 0; i--) {
            if (sorted[i] <= head) break;
        }

        for (j = i; j >= 0; j--) {
            seek_time += abs(head - sorted[j]);
            head = sorted[j];
            printf(" -> %d", head);
        }

        if (head != 0) {
            seek_time += abs(head - 0);
            head = 0;
        }

        for (j = i + 1; j < n; j++) {
            seek_time += abs(head - sorted[j]);
            head = sorted[j];
            printf(" -> %d", head);
        }
    }

    printf("\nTotal Seek Time: %d", seek_time);
    printf("\nAverage Seek Time: %.2f\n", (float)seek_time / n);
}

int main() {
    int disk_size, head, n, i;
    int requests[MAX];
    char direction[10];

    printf("Enter total number of cylinders (disk size): ");
    scanf("%d", &disk_size);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the request queue:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= disk_size) {
            printf("Invalid request: %d. Must be between 0 and %d.\n", requests[i], disk_size - 1);
            return 1;
        }
    }

    printf("Enter direction for SCAN (up/down): ");
    scanf("%s", direction);

    printf("\n--- Disk Scheduling Results ---\n");
    fcfs(requests, n, head);
    sstf(requests, n, head);
    scan(requests, n, head, disk_size, direction);

    return 0;
}

