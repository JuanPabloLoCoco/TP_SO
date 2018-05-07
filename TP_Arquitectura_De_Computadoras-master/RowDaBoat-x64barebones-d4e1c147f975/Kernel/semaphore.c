#include "include/semaphore.h"
#include "include/strings.h"
#include "include/mutex.h"
#include "include/process.h"
#include "include/scheduler.h"
#include "include/videoDriver.h"

void addToSemaphoreQueue(semaphore_t * semaphore, int pid);
int removeFromSemaphoreQueue(semaphore_t * semaphore);

void initSemaphore(semaphore_t * semaphore){
    semaphore->queueIndex=0;
    semaphore->queueSize=0;
}

void waitSemaphore(semaphore_t * semaphore, int mutex){
    lockScheduler();
    semaphore->mutex = mutex;
    addToSemaphoreQueue(semaphore,getCurrentPid());
    changeProcessState(getCurrentPid(),BLOCKED);
    unlockMutex(mutex);
    unlockScheduler();
    _yield();
    lockMutex(mutex);
}

void signalSemaphore(semaphore_t * semaphore){
    int pid = removeFromSemaphoreQueue(semaphore);
    if(pid != -1) changeProcessState(pid,READY);
}

void broadcastSemaphore(semaphore_t * semaphore){
    int notPreviouslyLocked=lockScheduler();
    int i,prevMax = semaphore->queueSize;
    for (i = 0; i < prevMax;i++){
        signalSemaphore(semaphore);
    }
    if(notPreviouslyLocked) unlockScheduler();
}

void addToSemaphoreQueue(semaphore_t * semaphore, int pid){
    if(semaphore->queueSize == MAX_SEMAPHORE_QUEUE_SIZE) return;
    int index = (semaphore->queueIndex + semaphore->queueSize)%MAX_SEMAPHORE_QUEUE_SIZE;
    semaphore->queue[index] = pid;
    semaphore->queueSize ++;
}

int removeFromSemaphoreQueue(semaphore_t * semaphore){
    if(semaphore->queueSize==0)return -1;
    int pid = semaphore->queue[semaphore->queueIndex];
    semaphore->queueIndex = (semaphore->queueIndex + 1) % MAX_SEMAPHORE_QUEUE_SIZE;
    semaphore->queueSize --;
    return pid;
}
