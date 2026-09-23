#include<stdio.h>
#include<stdint.h>
#include "queue.h"

Queue queue_new(uint32_t size){
    size = (size >0 && size <= MAX_QUEUE_LEN) ? size : MAX_QUEUE_LEN;

    Queue queue = {size,0,0,0,{0}};
    return queue;
}

Queue *queue_add(Queue *queue, uint32_t data,QueueResult *queueResult){
    if(queue->count<queue->size){
        queue->values[queue->tail]  =data;
        queue -> tail = (queue->tail+1) % queue->size;
        ++queue->count;
        queueResult->status = QUEUE_OK;
        queueResult->data = data;
    }else{
        queueResult->status = QUEUE_FULL;
        queueResult->data = RESULT_INVALID;
    }
    return queue;
}

Queue *queue_remove(Queue *queue, QueueResult *queueResult){
    if(queue->count>0){
        queueResult->data = queue->values[queue->head];
        queueResult->status = QUEUE_OK;
        queue->head = (queue->head+1) % queue->size;
        --queue->count;
    }else{
        queueResult->status = QUEUE_EMPTY;
        queueResult->data = RESULT_INVALID;
    }
    return queue;
}
Queue *queue_peek(const Queue *queue, QueueResult *queueResult){
    if(queue->count>0){
        queueResult->data = queue->values[queue->head];
        queueResult->status = QUEUE_OK;
    }else{
        queueResult->status = QUEUE_EMPTY;
        queueResult->data = RESULT_INVALID;
    }
    return (Queue *)queue;// can be written as return queue also, this specific will help the compiler know that return time of queue
}

uint32_t queue_isFull(const Queue * queue){
    return queue->count == queue->size;
}

uint32_t queue_isEmpty(const Queue *queue){
    return queue->count == 0;

}
uint32_t queue_length(const Queue *queue){
    return queue->count;
}

void queue_display(const Queue *queue, QueueResult *queueResult){
    if(queue->count>0){
        printf("Queue elements: ");
        for(uint32_t i=0;i<queue->count;i++){
            uint32_t index = (queue->head + i) % queue->size;
            printf("%d ", queue->values[index]);
        }
        printf("\n");
        queueResult->status = QUEUE_OK;
    }else{
        printf("Queue is empty.\n");
        queueResult->status = QUEUE_EMPTY;
    }
}


