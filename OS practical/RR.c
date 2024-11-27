#include <stdio.h>

void calculateRR(int n, int bt[], int at[], int ct[], int tat[], int wt[], int tq)
{
    int remaining_bt[n], time = 0, completed = 0;

    for (int i = 0; i < n; i++)
        remaining_bt[i] = bt[i];

    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (remaining_bt[i] > 0 && at[i] <= time)
            {
                if (remaining_bt[i] <= tq)
                {
                    time += remaining_bt[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    remaining_bt[i] = 0;
                    completed++;
                }
                else
                {
                    time += tq;
                    remaining_bt[i] -= tq;
                }
            }
        }
        time++; // Increment time if no process is ready
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
    int n, tq;
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

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    calculateRR(n, bt, at, ct, tat, wt, tq);
    printProcessInfo(n, bt, at, ct, tat, wt);

    return 0;
}
