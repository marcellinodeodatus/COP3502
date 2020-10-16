/*COP 3502 Assignment 2
This program is written by: Deodatus Marcellino */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
//#include "leak_detector_c.h"

// ******************* Structs ******************* //
typedef struct Queue
{
    char *queueName;      // group name
    int nodeCount;        // soldier numbers
    int groundNumber;     // group ID number
    int k;                //skipped
    int th;               //threshold
    int size;             //size of queue
    struct soldier *head; // this pointer here will store the front of the queue
    struct soldier *tail; // this pointer here will store the last element in the queue
} Queue;

typedef struct soldier
{
    int sequenceNumber;
    int soldierID[SIZE];
    struct soldier *prev;
    struct soldier *next;
} soldier;

// ****************** Function Prototype ************ //
soldier *createSoldier(int);
void init(Queue *);
void createReverseCircle(Queue *);
void rearrangeCircle(Queue *);
void enqueue(Queue *, int);
void display(int, Queue *);
void writeFile(FILE *, Queue *, int);
void displayQueue(Queue *);

// ******************* Main *********************** //
int main()
{
    // memory leak
    //atexit(report_mem_leak);

    // ********************* Variables **************** //
    char tempName[101];         //create a temp char variable that store 100 word
    int length = 0;             // create the length var that store the length of each name
    int tempSequenceNumber = 0; // create temporary variable to store number of soldiers
    int numberOfGrounds = 0;
    int tempNumber = 0;

    //  ***************** read from file ***************** //
    FILE *fp = fopen("in.txt", "r");
    // take in the total number of group from file
    fscanf(fp, "%d", &numberOfGrounds);

    // create an array of queue
    Queue *grounds[SIZE];

    for (int i = 0; i < numberOfGrounds; i++)
    {
        //scan the node / ground number
        fscanf(fp, "%d", &tempNumber);
        grounds[tempNumber - 1] = calloc(1, sizeof(Queue));
        init(grounds[tempNumber - 1]);
        grounds[tempNumber - 1]->groundNumber = tempNumber;

        //scan the name and get the length
        fscanf(fp, "%s", tempName);
        length = strlen(tempName);
        grounds[tempNumber - 1]->queueName = (char *)calloc(length + 1, sizeof(char));
        strcpy(grounds[tempNumber - 1]->queueName, tempName);

        // scan the number of soldiers
        fscanf(fp, "%d", &grounds[tempNumber - 1]->nodeCount);
        //
        for (int j = 0; j < grounds[tempNumber - 1]->nodeCount; j++)
        {
            enqueue(grounds[tempNumber - 1], j + 1);
        }

        // scan the number of k-skipped
        fscanf(fp, "%d", &grounds[tempNumber - 1]->k);

        // scan the number of threshold
        fscanf(fp, "%d", &grounds[tempNumber - 1]->th);
    }

    // reverse each queue
    for (int i = 0; i < SIZE; i++)
    {
        createReverseCircle(grounds[i]);
        displayQueue(grounds[i]);
    }

    // display queue
    printf("Initial nonempty lists status\n");

    for (int i = 0; i < numberOfGrounds; i++)
    {
        display(1, grounds[i]);
    }

    printf("After ordering nonempty lists status\n");
    for (int i = 0; i < numberOfGrounds; i++)
    {
        display(0, grounds[i]);
    }

    //phase 1
    // int counter = 1;
    // for (int i = 0; i < numberOfGrounds; i++)
    // {
    //     for (int j = 0; j < grounds[i]->th; j++)
    //     {
    //         if (counter == grounds[i]->k)
    //         {
    //             printf("%d", grounds[i]->head->sequenceNumber);
    //             counter = 0;
    //             grounds[i]->head->soldierID = 0;
    //         }

    //         grounds[i]->head = grounds[i]->head->next;
    //         counter++;
    //         // kill the k-th element
    //         // set the counter = 0
    //     }
    // }

    // write to file
    FILE *out = fopen("out.txt", "w"); // write to FILE
    fprintf(out, "Initial nonempty lists status\n");
    for (int i = 0; i < numberOfGrounds; i++)
    {
        writeFile(out, grounds[i], 1);
    }
    fprintf(out, "After ordering nonempty lists status\n");
    for (int i = 0; i < numberOfGrounds; i++)
    {
        writeFile(out, grounds[i], 0);
    }
    // freeing memory
    for (int k = 0; k < SIZE; k++)
    {
        free(grounds[k]->queueName);
    }
    free(grounds);

    // close the file
    fclose(fp);
    fclose(out);

    return 0;
} // end main

// ****************** Function ********************* //
void init(Queue *myQueue)
{
    myQueue->head = NULL;
    myQueue->tail = NULL;
    myQueue->size = 0;
}

void displayQueue(Queue *q)
{
    if (q->head == NULL)
        return;

    printf("%d ", q->groundNumber);
    printf("%s", q->queueName);

    soldier *current;

    current = q->head;
    while (current)
    {
        printf(" %d ", current->sequenceNumber);
        current = current->next;
    }
    printf("\n");
}

void writeFile(FILE *fp, Queue *q, int flag)
{
    soldier *current;
    if (q->head == NULL)
        return;

    fprintf(fp, "%d ", q->nodeCount);
    fprintf(fp, " %s ", q->queueName);
    if (flag == 0)
    {
        current = q->head;
        while (current)
        {
            fprintf(fp, " %d ", current->sequenceNumber);
            current = current->next;
        }
    }
    else if (flag == 1)
    {
        current = q->tail;
        while (current)
        {
            fprintf(fp, " %d ", current->sequenceNumber);
            current = current->prev;
        }
    }

    fprintf(fp, "\n");
}

soldier *createSoldier(int sequence)
{
    soldier *s = (soldier *)calloc(1, sizeof(soldier));
    s->sequenceNumber = sequence;
    //s->prev = NULL;
    //s->next = NULL;
    return s;
}

void enqueue(Queue *q, int value)
{
    // check if the queue is empty
    if (q->head == NULL)
    { // if the queue is empty, I just need to make a new node
        // and make the node as the front
        q->head = createSoldier(value);
        for (int i = 0; i <= value - 1; i++)
        {
            q->head->soldierID[i] = i + 1;
        }
        q->tail = q->head;
        q->size++;
        return;
    }

    // if the queue is full, return
    if (q->size == SIZE)
    {
        return;
    }
    // if the queue is not empty, add to the end of the queue
    soldier *temp;
    temp = createSoldier(value);
    for (int i = 0; i <= value - 1; i++)
    {
        temp->soldierID[i] = i + 1;
    }
    q->tail->next = temp;
    temp->prev = q->tail;
    q->tail = temp;
    q->size++;
    return;
}

void display(int flag, Queue *q)
{
    if (q->head == NULL)
        return;

    printf("%d ", q->nodeCount);
    printf("%s", q->queueName);

    soldier *current;
    if (flag == 0)
    {
        current = q->head;
        while (current)
        {
            printf(" %d ", current->sequenceNumber);
            current = current->next;
        }
    }
    else if (flag == 1)
    {
        current = q->tail;
        while (current)
        {
            printf(" %d ", current->sequenceNumber);
            current = current->prev;
        }
    }
    printf("\n");
}

void createReverseCircle(Queue *q)
{
    soldier *temp;
    soldier *cur = q->head;

    do
    {
        temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;

        cur = cur->prev;

    } while (cur != q->head);

    temp = q->head;
    q->head = q->tail;
    q->tail = temp;
}