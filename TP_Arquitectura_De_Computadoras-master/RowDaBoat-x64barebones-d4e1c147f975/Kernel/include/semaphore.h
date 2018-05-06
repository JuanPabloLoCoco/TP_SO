#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#define MAX_SEMAPHORE_NAME_LENGHT 50
#define MAX_SEMAPHORE_QUEUE_SIZE 50
#define MAX_SEMAPHORE 30


typedef struct {
    int queue[MAX_SEMAPHORE_QUEUE_SIZE];
    int queueSize;
    int queueIndex;
    int mutex;
}semaphore_t;

void initSemaphore(semaphore_t * semaphore);
void waitSemaphore(semaphore_t * semaphore, int mutex);
void signalSemaphore(semaphore_t * semaphore);
void broadcastSemaphore(semaphore_t * semaphore);

#endif //_Semaphore_H
