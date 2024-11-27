#include <stdio.h>

void calculateSJF(int n, int bt[], int at[], int ct[], int tat[], int wt[])
{
    int completed[n], time = 0, min_bt, min_index;
    for (int i = 0; i < n; i++)
        completed[i] = 0;

    for (int completed_count = 0; completed_count < n; completed_count++)
    {
        min_bt = 1e9; // A large value to find the minimum burst time
        min_index = -1;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && at[i] <= time && bt[i] < min_bt)
            {
                min_bt = bt[i];
                min_index = i;
            }
        }

        if (min_index == -1) // No process is ready, CPU idle
        {
            time++;
            continue;
        }

        // Process the selected job
        time += bt[min_index];
        ct[min_index] = time;
        tat[min_index] = ct[min_index] - at[min_index];
        wt[min_index] = tat[min_index] - bt[min_index];
        completed[min_index] = 1;
    }
}

void printProcessInfo(int n, int bt[], int at[], int ct[], int tat[], int wt[])
{
    printf("PID\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], at[i], ct[i], wt[i], tat[i]);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], ct[n], tat[n], wt[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
    }

    calculateSJF(n, bt, at, ct, tat, wt);
    printProcessInfo(n, bt, at, ct, tat, wt);

    return 0;
}
