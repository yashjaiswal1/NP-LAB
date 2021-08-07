#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define PACKET_SIZE 2;

struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int *array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue *createQueue(unsigned capacity)
{
    struct Queue *queue = (struct Queue *)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int *)malloc(
        queue->capacity * sizeof(int));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue *queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue *queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue *queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    printf("%d enqueued to queue\n", item);
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void main()
{
    int total_time = 0;
    int outflow_rate;
    int bucket_capacity;
    printf("What is the bucket capacity (in MBs)?\n");
    scanf("%d", &bucket_capacity);
    struct Queue *bucket = createQueue(bucket_capacity / 2);
    printf("What is the outflow rate of the bucket?\n");
    scanf("%d", &outflow_rate);
    int num_of_inputs;
    int current_memory = bucket_capacity;
    int temp;
    while (total_time != 10)
    { // upto 10 seconds
        printf("\nCurrent memory = %d\n", current_memory);
        printf("How many inputs from %d to %d seconds?\n", total_time, total_time + 1);
        scanf("%d", &num_of_inputs);
        if (num_of_inputs * 2 > current_memory)
        {
            printf("Packets REJECTED\n");
            continue;
        }

        while (num_of_inputs != 0)
        {
            printf("\nEnter packet:\n");
            scanf("%d", &temp);
            enqueue(bucket, temp);
            current_memory -= 2; // reduce 2MB for every packet
            num_of_inputs -= 1;
        }
        temp = outflow_rate;
        while (temp != 0 && isEmpty(bucket) != 1)
        {
            printf("Transmitted: %d\n", dequeue(bucket));
            current_memory += 2; // increase 2 MB for every packet transmitted
            temp -= 1;
        }

        total_time += 1;
    }
}
