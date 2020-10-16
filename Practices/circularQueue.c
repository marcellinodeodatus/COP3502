#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// here we define the initial capacity that the queue should have
#define INITIAL_CAP 10

typedef struct Queue
{
    int cap;   // the max number of elements it can hold
    int front; // the current index of the front element
    int size;  // the current size of the queue
    int *arr;  // the actual array that will hold the numbers
} Queue;

Queue *createQueue();
Queue *enqueue(Queue *, int);
int dequeue(Queue *);
int isEmpty(Queue *);
int peek(Queue *);
void freeQueue(Queue *);

int main()
{
    // create your queue. I will name it q so it's easy to write
    Queue *q = createQueue();

    // add some elements to the queue
    for (int i = 0; i < 10; i++)
    {
        q = enqueue(q, i + 1); // add the elements 1 through 10
    }

    // let's take a peek at what the front value in the list is currently
    printf("the current value at the front is %d\n", peek(q));

    // now let's dequeue a value
    // remember that the deqeueue function will remove the front element and then return it so the return type should be int
    printf("The value I just removed from the list is %d\n", dequeue(q));
    printf("That means that the front value is now %d\n", peek(q));

    // now that we are done using the queue we should free it
    freeQueue(q);

    // the limitations of this program are that we did not create a way to make the queue larger when we reach the max size
    // try to write a program that will reallocate for more space whenever the queue gets full as a challenge

    return 0;
}

Queue *createQueue()
{
    Queue *ret = (Queue *)calloc(1, sizeof(Queue));
    ret->cap = INITIAL_CAP;                          // give the queue the initial capacity stated at the top of the code
    ret->size = 0;                                   // the queue is just being created so it's current size will be 0
    ret->front = 0;                                  // initialize the front to 0 since we have no elements in the queue yet
    ret->arr = (int *)calloc(ret->cap, sizeof(int)); // allocate enough space in the array for the initial cap
    return ret;                                      // return the created queue
}

Queue *enqueue(Queue *q, int value)
{
    if (q->size == q->cap) // if the queue is full we can't add the value
    {
        printf("the queue is full\n");
        return q;
    }

    // if we get past the if statement above then the list is not full and we can just add the value
    // since it is a circular queue, we find where we need to add the value using the followng formula
    int index = (q->size + q->front) % q->cap;

    // then we add it to the queue
    q->arr[index] = value;

    // then we increase the size of the list by 1
    q->size++;

    // finally we return the queue pointer
    return q;
}

int isEmpty(Queue *q)
{
    if (q->size == 0)
        return 1; // return 1 when the list is emtpy
    else
        return 0; // return 0 when the list is not empty
}

int dequeue(Queue *q)
{
    // check if the queue is empty using the is empty function
    if (isEmpty(q)) // you could also say if(q->size == 0) to check if it is empty
    {
        // we don't need to remove anything since it is empty
        // we can just return something like -1 to show nothing was removed
        return -1;
    }

    // if we get past the above if statement that means that the list is not empty
    // so let's store the number at the front
    int value = q->arr[q->front];

    // and then make the new front be the next item in the list and then make the list size 1 smaller
    q->front = (q->front + 1) % q->cap; // we use the mod so that we don't go out of bounds
    q->size--;

    // now we return the value we had stored
    return value;
}

int peek(Queue *q)
{
    if (isEmpty(q))
    {
        // if the list is empty then there is nothing to peek so we can return something like -1
        return -1;
    }

    return q->arr[q->front];
}

void freeQueue(Queue *q)
{
    // start by freeing the members of the struct that were dynamically allocated
    free(q->arr);

    // now we free the queue
    free(q);
}