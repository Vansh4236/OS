#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3

int A[ROWS][COLS] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
int B[ROWS][COLS] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
};
int C[ROWS][COLS];

void* add_matrices(void* arg) {
    int index = *((int*)arg);  // Dereference to get the index
    for (int j = 0; j < COLS; j++) {
        C[index][j] = A[index][j] + B[index][j];
    }
    pthread_exit(0);
}

int main() {
    pthread_t threads[ROWS];
    int thread_args[ROWS];

    for (int i = 0; i < ROWS; i++) {
        thread_args[i] = i;
        // Passing a pointer to the index to the thread function
        pthread_create(&threads[i], NULL, add_matrices, (void*)&thread_args[i]);
    }

    for (int i = 0; i < ROWS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Result Matrix:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
  }

return 0;
}
