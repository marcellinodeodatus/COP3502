/******************************************************************************
COP3502C - Circular Doubly Linked List Queue
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// ************************************ Structs ************************************ //
// Queue implemented with a circular doubly linked list
typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// this struct allows us to create void pass by value functions
typedef struct Queue
{
    Node *head;
} Queue;
// ************************************ Function Prototype ************************************ //
void enqueue(Queue *, int);
Node *createNode(int);
void printQueue(Node *);
printQueueReverse(Node *);
// create your own dequeue function
// create your own free function

// ************************************      Main    ************************************ //
int main()
{
    // create the queue
    Queue *q = (Queue *)calloc(1, sizeof(Queue));
    q->head = NULL;

    // lets add some values to the queue
    for (int i = 0; i < 10; i++)
        enqueue(q, i + 1); // so that we add the numbers 1 through 10
    printQueue(q->head);
    printQueueReverse(q->head->prev);
    return 0;
}
// ************************************  Function  ************************************ //

Node *createNode(int value)
{
    Node *ret = (Node *)calloc(1, sizeof(Node));
    ret->data = value;
    // set the prev and next to NULL
    ret->next = ret->prev = NULL;
    return ret;
}

void enqueue(Queue *q, int value)
{
    Node *new = createNode(value);
    // check if the list is empty
    if (q->head == NULL)
    {
        // put the new node as the head of the list
        q->head = new;
        // since it is the only element in the list,
        // next -> head, and prev -> head
        q->head->next = q->head;
        q->head->prev = q->head;

        // make it simple into 1 line
        /*q->head->next = q->head->prev = q->head;*/

        // now that we added the node we can end the function
        return;
    }

    // what to do when the list is NOT empty

    // we make the new node point to the head since it will be the last node
    new->next = q->head;
    // we make the new node point to the old last node
    new->prev = q->head->prev;

    // the old last node's next pointer needs to point to the new node
    // another way to say new->prev->next is by saying q->head->prev->next
    new->prev->next = new;

    // we make the head point to new since it is the last element
    q->head->prev = new;
}

void printQueue(Node *head)
{
    // check if the list is empty (head is null)
    if (!head)
        return;

    Node *temp = head;
    // print the first value before moving to the second value
    printf("%d ->", head->data);
    // mvoe to the second value
    head = head->next;
    // loop while the current node is not the first node, which is head
    while (temp != head)
    {
        printf("%d ->", head->data);
        head = head->next;
    }

    printf("End\n");
}

printQueueReverse(Node *tail)
{
    if (tail == NULL)
        return;

    Node *temp = tail;

    printf("%d ->", tail->data);

    tail = tail->prev;
    while (temp != tail)
    {
        printf("%d ->", tail->data);
        tail = tail->prev;
    }

    printf("End\n");
}