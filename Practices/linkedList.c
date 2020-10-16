/******************************************************************************
COP3502C - Linked List
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// singly linked list node
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// prototypes
Node *addToFront(Node *, int);
Node *createNode(int); // create a node and puts the number into it
void printList(Node *);
Node *addToBack(Node *, int);
Node *removeHead(Node *);
Node *removeTail(Node *);
void freeList(Node *);
Node *removeN(Node *, int); // we pass the head and the number we want to delete

Node *addN(Node *, int, int); // we pass head, the number we want to add, and the place we want to add it in.

int main()
{
    // create the List
    Node *head = NULL; // the null shows that the list is empty

    // add a number to the front of the list
    head = addToFront(head, 1);
    head = addToFront(head, 2);

    // add a number to the back of the list
    head = addToBack(head, 5);

    // remove head of the list/ remove first element
    head = removeHead(head);
    head = removeHead(head);

    // remove the tail of the list / remove the last element
    head = removeTail(head);

    for (int i = 0; i < 10; i++)
    {
        head = addToBack(head, i + 1);
    }

    // remove a specific number in the list we want to delete
    head = removeN(head, 8);
    head = removeN(head, 7);

    // print function
    printList(head);

    // we need to free the data in the list
    freeList(head);

    return 0;
}

void printList(Node *head)
{
    // we need to visit every node and print its value
    if (head == NULL)
    {
        printf("End of List");
        return;
    }

    //print each node as we visit it
    printf("%d -> ", head->data);

    printList(head->next);
}

void freeList(Node *head)
{
    // we need to visit every node BUT we have to free in reverse order
    if (!head)
        return;

    freeList(head->next);
    free(head);
}

Node *addToBack(Node *head, int number)
{
    // we check to see if we are at the end or if the list is empty
    if (!head)
    {
        // we need to create the node that we want to add
        return createNode(number);
    }

    head->next = addToBack(head->next, number); // this is recursion
    return head;
}

Node *addToFront(Node *head, int number)
{
    // check if the list is empty
    if (head == NULL) // or write if (!head)
    {
        // we just need to create a new node and then return it
        Node *newNode = createNode(number);
        return newNode;
    }

    // if the list if not empty
    // new -> 5 -> 6 -> NULL
    // we need to replace the head with the new node
    Node *newNode = createNode(number);
    newNode->next = head;
    return newNode;
}

Node *createNode(int number)
{
    Node *ret = calloc(1, sizeof(Node));
    ret->data = number;
    ret->next = NULL;
    return ret;
}

Node *removeHead(Node *head)
{
    // if the list is empty
    if (!head)
        return head;

    // we need to free the first node that we are getting rid of
    // we don't want to lose the rest of the list
    Node *temp = head->next; // temp gets the next element after head
    free(head);              // we free the head
    head = temp;             // the temp will be the new head
    return head;
}

Node *removeTail(Node *head)
{
    if (!head)
        return head;

    if (head->next == NULL) // if there is only one element in the list
    {
        // all we have to do is free the only node that is in the list
        free(head);
        return NULL;
    }

    // get to the element you want to remove
    // we actually want to get to the element right before the one that needs to be removed

    if (head->next->next == NULL)
    {
        // we got to the element right before the one to be removed
        free(head->next);
        head->next = NULL;
        return head;
    }

    head->next = removeTail(head->next);
}

Node *removeN(Node *head, int number)
{
    Node *t;
    Node *temp;

    // check if the list is empty or if the list only have one element
    if (head == NULL)
    {
        return head;
    }
    // if head is equal to the number
    if (head->data == number)
    {
        temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    t = head;
    while (t->next != NULL && t->next->data != number)
    {
        t = t->next;
    }
    if (t->next == NULL)
        return head;

    temp = t->next;
    t->next = t->next->next;
    free(temp);
    return head;
}

Node *addN(Node *, int, int)
// we pass head, the number we want to add, and the place we want to add it in.
{
}
