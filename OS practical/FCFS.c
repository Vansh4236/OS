#include <stdio.h>

void calculateTimes(int n, int bt[], int at[], int ct[], int tat[], int wt[])
{
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (at[j] > at[j + 1])
            {
                // Swap arrival times
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                // Swap burst times
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
            }
        }
    }

    // Calculate Completion Time
    ct[0] = at[0] + bt[0];
    for (int i = 1; i < n; i++)
    {
        if (at[i] > ct[i - 1])
        {
            // CPU is idle
            ct[i] = at[i] + bt[i];
        }
        else
        {
            ct[i] = ct[i - 1] + bt[i];
        }
    }

    // Calculate Turnaround Time and Waiting Time
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
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

    calculateTimes(n, bt, at, ct, tat, wt);
    printProcessInfo(n, bt, at, ct, tat, wt);

    return 0;
}
