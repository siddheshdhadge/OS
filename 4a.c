#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE], in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        int item = rand() % 100; // Generate a random item

        sem_wait(&empty);               // Wait for an empty slot
        pthread_mutex_lock(&mutex);     // Enter critical section

        buffer[in] = item;              // Add item to buffer
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;    // Update buffer index

        pthread_mutex_unlock(&mutex);    // Exit critical section
        sem_post(&full);                // Signal that a new item has been produced
    }
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);               // Wait for a full slot
        pthread_mutex_lock(&mutex);    // Enter critical section

        int item = buffer[out];        // Remove item from buffer
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Update buffer index

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&empty);              // Signal that an item has been consumed
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);         // Initialize empty slots
    sem_init(&full, 0, 0);                    // Initialize full slots
    pthread_mutex_init(&mutex, NULL);         // Initialize mutex

    pthread_create(&prod, NULL, producer, NULL); // Create producer thread
    pthread_create(&cons, NULL, consumer, NULL);  // Create consumer thread

    pthread_join(prod, NULL);                 // Wait for producer to finish
    pthread_join(cons, NULL);                 // Wait for consumer to finish

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

/*
svpmit23@svpmit23-HP-EliteDesk-800-G2-SFF:~/AnishaOsPracticals$ gcc P4A.c -lpthread
svpmit23@svpmit23-HP-EliteDesk-800-G2-SFF:~/AnishaOsPracticals$ ./a.out
Produced: 83
Produced: 86
Produced: 77
Produced: 15
Produced: 93
Consumed: 83
Consumed: 86
Consumed: 77
Consumed: 15
Consumed: 93
Produced: 35
Produced: 86
Produced: 92
Produced: 49
Produced: 21
Consumed: 35
Consumed: 86
Consumed: 92
Consumed: 49
Consumed: 21

*/
