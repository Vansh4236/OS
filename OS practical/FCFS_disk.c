#include<stdio.h>

void fcfs_scheduling(int request[],int n,int head)
{
    int total_head_movement=0;
    int current_position=head;

    printf("Order of Servicing:\n");
    for(int i=0;i<n;i++)
    {
        printf(" %d ",request[i]);

        int movement=current_position-request[i];
        if(movement < 0)
        {
            movement=-movement;
        }
        total_head_movement+=movement;

        current_position=request[i];
    }
    printf("\nTotal head movement:%d",total_head_movement);
}
int main()
{
    int n,head;
    printf("Enter number of services:");
    scanf("%d",&n);

    int request[n];
    printf("Enter the order of services:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&request[i]);
    }
    printf("Enter the initial head position:");
    scanf("%d",&head);

    fcfs_scheduling(request,n,head);
    return 0;
}