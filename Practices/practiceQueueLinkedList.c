#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct Queue
{
    int id;
    //char name;
    Node *head;
    Node *tail;
} Queue;

void createReverseCircle(Queue *);
void display(Node *);
void enqueue(Queue *, int);
Node *createNode(int);

int main()
{
    int temp;
    int tempID;
    Queue *list[10];

    for (int i = 0; i < 10; i++)
    {
        list[i] = calloc(1, sizeof(Queue));
        list[i]->head = NULL;

        for (int j = 0; i < 10; i++)
        {
            enqueue(list[i], i + 1); // so that we add 10 - 1
        }

        display(list[i]->head);
    }
    // fill the list with stuff

    //createReverseCircle(list);

    //FILE *fp = fopen("in.txt", "r");
    //fscanf(fp, "%d", &temp);
    for (int k = 0; k < 10; k++)
    {
        free(list[k]);
    }
    free(list);

} // end of main

Node *createNode(int value)
{
    Node *ret = (Node *)calloc(1, sizeof(Node));
    ret->data = value;
    ret->next = ret->prev = NULL;
    return ret;
}

void enqueue(Queue *queue, int value)
{
    Node *new = createNode(value);

    // check if the list is empty
    if (!queue->head)
    {
        queue->head = new;
        queue->head->next = queue->head->prev = queue->head;
        return;
    }

    new->next = queue->head;
    new->prev = queue->head->prev;
    new->prev->next = new;
    queue->head->prev = new;
}

void createReverseCircle(Queue *q)
{
    Node *temp = NULL;
    Node *current = q->head;

    do
    {
        // swap the prev and next nodes
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;

        current = current->prev;

    } while (current != q->head);

    temp = q->head;
    q->head = q->tail;
    q->tail = temp;
}

void display(Node *head)
{
    // check if the list is empty
    if (!head)
        return;
    //store the head in a temp variable
    Node *temp = head;
    // print the first value before moving to the second value
    printf("%d ", head->data);
    // move to the second value
    head = head->next;
    // loop while the current node is not the first node
    while (temp != head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("======================\n");
}