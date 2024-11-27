#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0; // Pointers for producer and consumer
sem_t empty, full;   // Semaphore for empty and full slots
pthread_mutex_t mutex;

void *producer(void *arg)
{
    for (int i = 0; i < 10; i++) // Produce 10 items
    {
        sem_wait(&empty); // Wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = i; // Produce an item
        printf("Producer produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Signal full slot
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < 10; i++) // Consume 10 items
    {
        sem_wait(&full); // Wait for full slot
        pthread_mutex_lock(&mutex);

        int item = buffer[out]; // Consume an item
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Signal empty slot
    }
    return NULL;
}

int main()
{
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
