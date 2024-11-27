#include <stdio.h>
#include <stdbool.h>

void calculate_need(int need[][10], int max[][10], int alloc[][10], int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool is_safe(int processes, int resources, int avail[], int max[][10], int alloc[][10]) {
    int need[10][10];
    calculate_need(need, max, alloc, processes, resources);

    bool finish[10] = {false};
    int safe_sequence[10];
    int work[10];

    for (int i = 0; i < resources; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < processes) {
        bool found = false;

        for (int p = 0; p < processes; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int r = 0; r < resources; r++) {
                    if (need[p][r] > work[r]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int r = 0; r < resources; r++) {
                        work[r] += alloc[p][r];
                    }
                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int processes, resources;
    int alloc[10][10], max[10][10], avail[10];

    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input maximum requirement matrix
    printf("Enter the maximum requirement matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &avail[i]);
    }

    // Check if the system is in a safe state
    is_safe(processes, resources, avail, max, alloc);

    return 0;
}