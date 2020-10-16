#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

Node *insert(Node *currentNode, int value);
Node *del(Node *currentNode, int d);
void print(Node *currentNode);
void freeList(Node *currentNode);
void copy(Node *source, Node **destination);

int main()
{
    // memory leak detector
    atexit(report_mem_leak);
    int number = 0, choice = 0;
    struct Node *pList = NULL;
    struct Node *nList = NULL;
    // Let the user add values until they enter -1.

    while (choice != 4)
    {
        //get the operation
        printf("\nDo you want to:\n(1)Insert\n(2)Delete\n(3)Copy\n(4)Quit.\n");
        scanf("%d", &choice);

        printf("Your choice is %d\n", choice);
        //execute the operation

        if (choice == 1)
        {
            //get the number
            printf("Enter the value to insert: ");
            scanf("%d", &number);
            pList = insert(pList, number);
            // look at the list
            printf("\nItems in the linked list: ");
            print(pList);
            printf("\n");
        }
        else if (choice == 2)
        {
            printf("Enter the value to delete: ");
            scanf("%d", &number);
            pList = del(pList, number);
            // look at the list
            printf("Items in Linked List: ");
            print(pList);
            printf("\n");
        }
        else if (choice == 3)
        {
            if (nList)
                freeList(nList);
            copy(pList, &nList); // passing reference of nList as it is not returning anything
            // Look at the list
            printf("Items in NEW linked list: ");
            print(nList);
            printf("\n");
        }
        else
        {
            break;
        }
    }
    freeList(nList);
    freeList(pList);
    printf("\nBye...\n");
    return 0;
} // end main function

Node *insert(Node *currentNode, int value)
{
    // if 'current' reaches the end of the list, or
    // if 'current' reaches the node where the value is bigger than or equal to the new value.
    if (currentNode == NULL || currentNode->value >= value)
    {
        // create a new node and insert the value to the node.
        Node *newNode = malloc(sizeof(Node));
        newNode->value = value;
        // create connection from the newNode to the next node.
        newNode->next = currentNode;
        return newNode;
    }

    currentNode->next = insert(currentNode->next, value);
    // if there is no basecase
    return currentNode;
}

Node *del(Node *currentNode, int value)
{
    // 1st basecase: if there is nothing to delete
    if (currentNode == NULL)
    {
        return NULL;
    }
    // 2nd basecase: if currentNode contains the value I want to delete
    else if (currentNode->value == value)
    {
        // put the next node in a temp, delete the current node,
        // then return temp so it will make the connection to the previous node.
        Node *temp = currentNode->next;
        // free the current node
        free(currentNode);
        return temp;
    }

    currentNode->next = del(currentNode->next, value);
    return currentNode;
}

void copy(Node *source, Node **destination)
{
    //if the list is not null
    if (source != NULL)
    {
        (*destination) = malloc(sizeof(Node));
        (*destination)->value = source->value;
        (*destination)->next = NULL;
        copy(source->next, &((*destination)->next));
    }
}

void print(Node *currentNode)
{
    if (currentNode != NULL)
    {
        printf("%d", currentNode->value);
        print(currentNode->next);
    }
}

void freeList(Node *currentNode)
{
    if (currentNode != NULL)
    {
        freeList(currentNode->next);
    }
    free(currentNode);
}