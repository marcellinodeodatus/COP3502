/********************* 
*   Lab 5 Queue Linked List
*
***********************/
#include <stdio.h>
#include <stdlib.h>

#define EMPTY -9999999

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct queue
{
    node *front;
    node *back;
} queue;

// ****************** function prototypes ****************** //
void init(queue *);
void enqueue(queue *, int);
int dequeue(queue *);
int front(queue *);
int empty(queue *);
void displayQueue(queue *);
// ****************** Main ******************//
int main()
{
    queue *myQueue = malloc(sizeof(queue));
    init(myQueue);

    int choice;
    int data;

    while (1)
    {
        printf("\n1. Insert element to queue \n");
        printf("2. Delete element from queue \n");
        printf("3. Display all elements of queue \n");
        printf("4. Quit \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nWhat data you want to put in the queue?: ");
            scanf("%d", &data);
            enqueue(myQueue, data);
            displayQueue(myQueue);
            break;
        case 2:
            data = dequeue(myQueue);
            if (data != EMPTY)
            {
                printf("\n%d deleted from queue\n", data);
                displayQueue(myQueue);
            }
            else
                printf("Empty queue\n");
            break;
        case 3:
            displayQueue(myQueue);
            break;
        case 4:
            exit(1);
        default:
            printf("Wrong choice \n");
        } // end switch

    } // end while-loop
} // end main

// ****************** functions ****************** //
void init(queue *myQueue)
{
    myQueue->front = NULL;
    myQueue->back = NULL;
}

/*enqueue
a)Create a new node and store the inserted value into it.
b)Link the back node's next pointer to this new node. 
c)Move the back node to point to the newly added node.
*/
void enqueue(queue *myQueue, int val)
{
    // a)Create a new node and store the inserted value into it.
    node *newNode = malloc(sizeof(node));
    newNode->data = val;
    newNode->next = NULL;

    // b)Link the back node's next pointer to this new node.
    if (myQueue->back != NULL)
    {
        myQueue->back->next = newNode;
    }
    // c)Move the back node to point to the newly added node.
    myQueue->back = newNode;

    if (myQueue->front == NULL)
    {
        myQueue->front = newNode;
    }
}

/*dequeue
a)Store a temporary pointer to the beginning of the list. 
b)Move the front pointer to the next node in the list. 
c)Free the memory pointed to by the temporary pointer.
*/
int dequeue(queue *myQueue)
{
    if (myQueue->front == NULL && myQueue->back == NULL)
    { // if the queue is empty
        return EMPTY;
    }
    int res = myQueue->front->data;

    // a)Store a temporary pointer to the beginning of the list.
    node *temp = myQueue->front;

    // b)Move the front pointer to the next node in the list.
    myQueue->front = myQueue->front->next;

    // if now the queue is empty, set back equals to NULL.
    if (myQueue->front == NULL)
    {
        myQueue->back = NULL;
    }

    // c)Free the memory pointed to by the temporary pointer.
    free(temp);

    return res;
}

/*front
Directly access the data stored in the first node through the front pointer to the list. 
*/
int front(queue *myQueue)
{
    int result;
    result = myQueue->front->data;
    return result;
}

/*empty:           
 Check if both pointers (front, back) are null.
 */
int empty(queue *myQueue)
{
    // if(myQueue->front == NULL && myQueue->back == NULL)
    // {
    //     return 1;
    // } else {
    //     return 0;
    // }
    return (myQueue->front == NULL && myQueue->back == NULL);
}

void displayQueue(queue *myQueue)
// traversing the list
{
    node *t = myQueue->front;
    while (t)
    {
        printf("%d", t->data);
        t = t->next;
    }
}
