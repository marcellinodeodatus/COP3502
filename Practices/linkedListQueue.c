#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is called a wrapper struct
// it will allow us to edit the queue in pass-by-value functions
typedef struct Queue
{
    struct Node *front; // this pointer here will store the front of the queue
    struct Node *back;  // this pointer here will store the last element in the queue
    int size;           // this will store the size of the queue because we can so why not
} Queue;

// this is just like any other linked list struct
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void enqueue(Queue *, int);
Node *createNode(int);
void printQueue(Queue *);
int peek(Queue *);
int dequeue(Queue *);
void freeQueue(Queue *);

int main()
{
    // create your queue. I'll name it q for ease of typing. You could also do this in its own function to make it prettier
    Queue *q = (Queue *)calloc(1, sizeof(Queue));
    q->front = q->back = NULL;
    q->size = 0;

    // now let's add some values to the queue
    for (int i = 0; i < 10; i++)
    {
        enqueue(q, i + 1);
    }

    // let's print all the values to make sure it is working
    printQueue(q);

    // let's peek to see what the first value is
    printf("The first value in the queue is %d\n", peek(q));

    // now let's dequeue from the list
    printf("The element we just removed is %d\n", dequeue(q));

    // peek again
    printf("The first value in the queue is %d\n", peek(q));

    // free the queue
    freeQueue(q);

    return 0;
}

Node *createNode(int data)
{
    Node *ret = (Node *)calloc(1, sizeof(Node));
    ret->data = data;
    ret->next = NULL;
    return ret;
}

void printQueue(Queue *q)
{
    Node *current = q->front;

    for (int i = 0; i < q->size; i++)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("End\n");
}

void enqueue(Queue *q, int value)
{
    // check if the queue is empty
    if (q->size == 0) // another way we can check: if(q->front == NULL)
    {
        // if the queue is empty we just need to make a new node and make it the new front as well as the new back
        q->front = createNode(value);
        q->back = q->front;
        // increase the size of the list by one
        q->size++;
        // end the function here since we are done adding
        return;
    }

    // if the queue is not empty then we need to add to the end of the queue
    // since we have a pointer to the last element in the queue we do not need to iterate to the back
    // we just need to make the back's next node be the new node
    q->back->next = createNode(value);
    // then we set the back to be the new node
    q->back = q->back->next;
    // then we increase the size of the list by 1
    q->size++;
}

int peek(Queue *q)
{
    // check if the list is empty
    if (q->size == 0)
        return -1; // return a number like -1 to show it is empty

    // otherwise just return the front element
    return q->front->data;
}

int dequeue(Queue *q)
{
    // check if it is empty
    if (!q->size)
        return -1;

    // we need to remove the first element
    // store the number in the first element
    int value = q->front->data;
    // we store the second element so we don't lose it
    Node *temp = q->front->next;
    // free the first element
    free(q->front);
    // make the second element the new first element
    q->front = temp;
    // decrease the size of the list by 1
    q->size--;

    // return the value that used to be the first element
    return value;
}

void freeList(Node *head)
{
    if (!head)
        return;
    freeList(head->next);
    free(head);
}

void freeQueue(Queue *q)
{
    // free it from the inside out

    // so start with the list by using the normal linked list free function
    freeList(q->front);
    // now free the queue pointer
    free(q);
}