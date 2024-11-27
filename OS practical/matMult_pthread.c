#include<stdio.h>
#include<pthread.h>

#define MAX 10

int mat1[MAX][MAX],mat2[MAX][MAX],result[MAX][MAX];
int row1,col1,row2,col2;

typedef struct
{
    int row;
    int col;
}thread_data;

void *multiply(void *arg){
    thread_data data=*(thread_data *)arg;
    int sum=0;
    for(int i=0;i<col1;i++)
    {
        sum += mat1[data.row][i]*mat2[i][data.col];
    }
    result[data.row][data.col] = sum;
    pthread_exit(0);
}

int main()
{  // Input dimensions of matrices
    printf("Enter the number of rows and columns for Matrix 1: ");
    scanf("%d%d", &row1, &col1);
    printf("Enter the number of rows and columns for Matrix 2: ");
    scanf("%d%d", &row2, &col2);

    if (col1 != row2) {
        printf("Matrix multiplication not possible. Columns of Matrix 1 must equal rows of Matrix 2.\n");
        return 1;
    }

    // Input Matrix 1
    printf("Enter elements of Matrix 1 (%d x %d):\n", row1, col1);
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    // Input Matrix 2
    printf("Enter elements of Matrix 2 (%d x %d):\n", row2, col2);
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }
//creationof thread
pthread_t thread[MAX][MAX];
thread_data data[MAX][MAX];

for(int i=0;i<row1;i++)
{
    for(int j=0;j<col2;j++)
    {
        data[i][j].row=i;
        data[i][j].col=j;

        pthread_create(&thread[i][j],NULL,multiply,&data[i][j]);
    }
}

for(int i=0;i<row1;i++)
{
    for(int j=0;j<col2;j++)
    {
        pthread_join(thread[i][j],NULL);
    }
}
printf("Resulta nt Matrix(%d*%d):n",row1,col2);
for(int i=0;i<row1;i++)
{
    for(int j=0;j<col2;j++)
    {
        printf("%d ",result[i][j]);
    }
    printf("\n");
}
return 0;
}
