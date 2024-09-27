#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
The program below should do the following:
- Creates four queues using dynamically linked list approach:
highPriorityQueue, mediumPriorityQueue, lowPriorityQueue, and trackerQueue.
- Enqueues 5 integers into each of the xPriorityQueues at initialization.
- After initialization, the program will enqueue one item to high, medium, and low priority queues on every iteration, however,
the dequeuing will happen based on the priority as follows:
Dequeuing from high priority queue happens first. If the high priority queue is empty, medium priority queue is dequeued.
If both high and medium priority queues are empty, low priority queue is dequeued.
- For every iteration, the program prints out the contents of all xPriorityQueues.
- trackerQueue is implemented to keep track of the dequeued items which is printed out at the end.
- At the end of the program, all queues are deleted and associated memory is freed.

Requirements:
- Complete writing the functions as described in the function documentation comments.
- Function signature must be not be changed. (Do not add/remove/modify any function parameter nor its return type)
- main() function must not be modified.
- Global declarations must not be modified.
*/

/******************************************************************************************
 * Student Name: Amar Singh
 * Student Number: 8935727
 */

#define ARRAY_SIZE(a)   (sizeof(a)/sizeof(a[0]))

// Structure for the queue node
typedef struct QueueNode
{
    int data;
    struct QueueNode* next;
} QueueNode_t;

// Structure for the queue
typedef struct
{
    QueueNode_t* front;
    QueueNode_t* rear;
} Queue_t;

/** 
 * @brief This function initializes a queue.
 * 
 * @param [out] queue - Pointer to queue structure.
 **/
void initializeQueue(Queue_t* queue)
{   
    // if you are passing a NULL pointer
    if(queue == NULL)
    {
        printf("Error: you are passing a NULL pointer\n");
        return;
    }
    queue->front = NULL;
    queue->rear = NULL;
}

/** 
 * @brief This function checks if a queue is empty
 * @param [in] queue - Pointer to queue structure.
 * @return True if queue is empty.
 **/

int isQueueEmpty(Queue_t* queue)
{
    // if you are passing a NULL pointer
    if(queue == NULL)
    {
        printf("Error: you are passing a NULL pointer\n");
        return 0;
    }

    if(queue->front == NULL)
    return 1;
    
    return 0;
    
}

/**
 * @brief This function enqueues data into a queue.
 * 
 * @param [in/out] queue - Pointer to queue structure.
 * @param [in] data - Data to be enqueued.
 **/
void enqueue(Queue_t* queue, int data)
{
    // if you are passing a NULL pointer
     if(queue == NULL)
    {
        printf("Error: You are passing a NULL pointer \n");
        return;
    }
    
   QueueNode_t* NewNode = (QueueNode_t*)malloc(sizeof(QueueNode_t));
   if(NewNode == NULL)
   {
       printf("Memory allocation failed\n");
       exit(0);
   }
   NewNode->data = data;
   NewNode->next = NULL;
   
   if(isQueueEmpty(queue))
   {
       queue->rear = NewNode;
       queue->front = NewNode;  
   }
   else
   {
      queue->rear->next = NewNode;
      queue->rear = NewNode;
   }
   
}

/**
 * @brief This function dequeues data from a queue.
 * 
 * @param [in/out] queue - Pointer to queue structure.
 * @return Dequed data, returns -1 if queue is empty
 **/
int dequeue(Queue_t* queue)
{
    // if we are passing a NULL pointer
    if(queue == NULL)
    {
        printf("Error: You are passing a NULL pointer \n");
        return 0;
    }

    // if the queue is empty
    if(isQueueEmpty(queue))
    return 0;
    
    int Data = queue->front->data;
    QueueNode_t* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return Data;
    
}

/**
 * @brief This function prints the contents of a queue
 * 
 * @param [in] queue - Pointer to queue structure.
 * @param [in] queueName - Pointer to a string that represents the queue name.
 **/
void printQueue(Queue_t* queue, const char* queueName)
{
    // if the pointer we are passing is NULL 
    if(queue == NULL)
    {
        printf("Error: NULL pointer is passed\n");
        return;
    }

    // if we are passing the NULL to queueName
     if(queueName == NULL)
    {
        printf("Please specify the Queue name\n");
        return;
    }
    
    // if the queue is empty
    if(isQueueEmpty(queue))
    {
    printf("%s is empty\n", queueName);
    return;
    }

    printf("%s ", queueName);  
    QueueNode_t* temp = queue->front;
    while(temp != NULL)
     {
             printf("%d ", temp->data);
             temp = temp->next;
     }
  
             printf("\n");
}

/**
 * @brief This function dequeues one item based on priority.
 * Dequeue from high priority queue first. If the high priority queue is empty, try medium priority.
 * If both high and medium priority queues are empty, try low priority.
 *
 * @param [in/out] highPriorityQueue - Pointer to high priority queue.
 * @param [in/out] highPriorityQueue - Pointer to medium priority queue.
 * @param [in/out] highPriorityQueue - Pointer to low priority queue.
 * @param [out] trackerQueue - Pointer to the tracker queue
 **/
void dequeueBasedOnPriority(Queue_t* highPriorityQueue, Queue_t* mediumPriorityQueue, Queue_t* lowPriorityQueue, Queue_t* trackerQueue)
{
      // if you are passing a NULL pointer
        if(highPriorityQueue == NULL || mediumPriorityQueue == NULL || lowPriorityQueue == NULL || trackerQueue == NULL)
        {
            printf("Error: You are passing NULL pointer\n");
            return;
        }

        if(isQueueEmpty(highPriorityQueue))
        {
            if(isQueueEmpty(mediumPriorityQueue))
            {
                 int data = dequeue(lowPriorityQueue);
                 enqueue(trackerQueue, data);
            }
            else
            {
                int data = dequeue(mediumPriorityQueue);
                enqueue(trackerQueue, data);
            }
        }
        else
        {
            int data = dequeue(highPriorityQueue);
            enqueue(trackerQueue, data);
        }
}

/**
 * @brief This function deletes all queues by freeing the associated memory for each queue
 * @param[in] queueType - Pointer to array of queues
 * @param[in] numberOfQueues - Represents the length of the passed array
 */
void deleteQueues(const Queue_t *queueType, uint8_t numberOfQueues)
{
    int i;
    for(i = 0; i < numberOfQueues; i++)
    {
        QueueNode_t* current = queueType[i].front;
        while (current != NULL)
        {
            QueueNode_t* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main()
{
    Queue_t highPriorityQueue, mediumPriorityQueue, lowPriorityQueue, trackerQueue;
    initializeQueue(&highPriorityQueue);
    initializeQueue(&mediumPriorityQueue);
    initializeQueue(&lowPriorityQueue);
    initializeQueue(&trackerQueue);

    // Enqueue some initial data
    int i;
    for (i = 1; i <= 5; i++) {
        enqueue(&highPriorityQueue, i + 10);
        enqueue(&mediumPriorityQueue, i + 20);
        enqueue(&lowPriorityQueue, i + 30);
    }

    printQueue(&highPriorityQueue, "High Priority");
    printQueue(&mediumPriorityQueue, "Medium Priority");
    printQueue(&lowPriorityQueue, "Low Priority");
    printf("\n");
    
    int iteration;
    for (iteration = 1; iteration <= 10; iteration++) {
        int dequeuedItem = -1;

        dequeueBasedOnPriority(&highPriorityQueue, &mediumPriorityQueue, &lowPriorityQueue, &trackerQueue);
        dequeueBasedOnPriority(&highPriorityQueue, &mediumPriorityQueue, &lowPriorityQueue, &trackerQueue);

        // Enqueue a new item in all queues for each iteration
        enqueue(&highPriorityQueue, 100 + iteration);
        enqueue(&mediumPriorityQueue, 110 + iteration);
        enqueue(&lowPriorityQueue, 120 + iteration);

        // Print the contents of high, medium, and low priority queues
        printf("Iteration %d:\n", iteration);
        printQueue(&highPriorityQueue, "High Priority");
        printQueue(&mediumPriorityQueue, "Medium Priority");
        printQueue(&lowPriorityQueue, "Low Priority");
        printf("\n");
    }

    
    printf("Contents of Tracker Queue:\n");
    printQueue(&trackerQueue, "Tracker");
    printf("\n");

    // Free allocated memory for all queues
    const Queue_t queueType[] =
    {
        highPriorityQueue, 
        mediumPriorityQueue, 
        lowPriorityQueue, 
        trackerQueue
    };
    deleteQueues(queueType, ARRAY_SIZE(queueType));
    
    return 0;
}
