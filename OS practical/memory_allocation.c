#include <stdio.h>

void First_Fit(int block_size[], int m, int process_size[], int n)
{
   

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (block_size[j] >= process_size[i])
            {
                printf("Process %d allocated to %d memory blocks\n",i+1,j+1);
                block_size[j] -= process_size[i];
                break;
            }
        }
    }
    
}

void Best_Fit(int block_size[], int m, int process_size[], int n)
{
    
    for (int i = 0; i < n; i++)
    {
        int best_index = -1;
        for (int j = 0; j < m; j++)
        {
            if(block_size[j] > process_size[i])
            {
                if(best_index == -1 || block_size[j] < block_size[best_index])
                {
                    best_index=j;
                }
            }
        }

        if(best_index != -1)
        {
            printf("Process %d allocated to %d memory blocks\n",i+1,best_index+1);
            block_size[best_index] -= process_size[i];
        }
    }
    
}

void Worst_Fit(int block_size[],int m,int process_size[],int n)
{
    for(int i=0;i<n;i++)
    {
        int worst_index = -1;
        for(int j=0;j<m;j++)
        {
            if(block_size[j] >= process_size[i])
            {
                if(worst_index == -1 || block_size[j] > block_size[worst_index])
                {
                    worst_index = j;
                }
            }
        }
        if(worst_index != -1)
        {
            printf("Process %d allocated to %d memory blocks\n",i+1,worst_index+1);
            block_size[worst_index] -= process_size[i];
        }
    }
    
}
int main()
{
    int m, n;

    // Input number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    int block_sizes[m];
    printf("Enter the sizes of memory blocks:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &block_sizes[i]);
    }

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process_sizes[n];
    printf("Enter the sizes of processes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &process_sizes[i]);
    }

    // Perform First Fit memory allocation
    printf("First Fit\n\n");
    First_Fit(block_sizes, m, process_sizes, n);
    printf("Best Fit\n\n");
    Best_Fit(block_sizes, m, process_sizes, n);
    printf("Worst Fit\n\n");
    Worst_Fit(block_sizes, m, process_sizes, n);
    return 0;
}