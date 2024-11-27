#include <stdio.h>

int absolute(int value)
{
    if (value < 0)
    {
        return -value;
    }
    else
    {
        return value;
    }
}

void scan(int request[], int n, int head, int disk_size, int direction)
{
    int total_head_movement = 0;
    int current_position = head;

    // Sort the requests
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (request[j] > request[j + 1])
            {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    printf("Order of Servicing:\n");
    if (direction == 1)
    {
        // Move towards higher tracks
        for (int i = 0; i < n; i++)
        {
            if (request[i] > head)
            {
                printf("%d ", request[i]);
                total_head_movement += absolute(current_position - request[i]);
                current_position = request[i];
            }
        }

        // Move head to the end of disk
        if (current_position < disk_size - 1)
        {
            total_head_movement += absolute(current_position - (disk_size - 1));
            current_position = disk_size - 1;
        }

        // Reverse direction service
        for (int i = n - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                printf("%d ", request[i]);
                total_head_movement += absolute(current_position - request[i]);
                current_position = request[i];
            }
        }
    }
    else
    {
        // Move towards lower tracks
        for (int i = n - 1; i >= 0; i--)
        {
            if (request[i] < head)
            {
                printf("%d ", request[i]);
                total_head_movement += absolute(current_position - request[i]);
                current_position = request[i];
            }
        }

        // Move head to the start of disk
        if (current_position > 0)
        {
            total_head_movement += absolute(current_position - 0);
            current_position = 0;
        }

        // Reverse direction service
        for (int i = 0; i < n; i++)
        {
            if (request[i] > head)
            {
                printf("%d ", request[i]);
                total_head_movement += absolute(current_position - request[i]);
                current_position = request[i];
            }
        }
    }

    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

int main()
{
    int n = 0, head, disk_size, direction;

    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter requests (track numbers):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("Enter starting head position: ");
    scanf("%d", &head);

    printf("Enter direction (1 for end of disk, 0 for start of disk): ");
    scanf("%d", &direction);

    if (direction != 0 && direction != 1)
    {
        printf("Invalid direction. Please enter 0 or 1.\n");
        return 1;
    }

    scan(request, n, head, disk_size, direction);

    return 0;
}
