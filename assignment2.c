/* COP3502
** Programming Assignment 2 - Linked list & Queue
** Name: Deodatus Marcellino
** Spring 2021 
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_Namesize 10

// ************** Structs *************** // 
typedef struct customer {
    char name[MAX_Namesize+1];
    int time;
    int line_number;
    int num_items;
} customer;

typedef struct customers_list {
    customer* customerPtr;
    struct customers_list* next;
} customers_list;

typedef struct queue {
    customers_list* front;
    customers_list* back;
} queue;

// ************** Restrictions & Defined Constants ************ //
const int TIME = 1000000000;
const int LINES = 12;
const int max_total_items = 100;


const int NUM_OF_SECONDS = 30;
const int time_processItem = 5;

// ************ Funtions Prototype ************ // 
void initQueue(queue* qPtr);
void enqueue(queue* qPtr, customers_list* newNode);
void free_node(customers_list* ptrNode);
customers_list* dequeue(queue* qPtr);
customer* front_customer(queue* qPtr); //similar to peek()
customer* createNode_customer(char* name, int time, int line, int num_items);
int linePriority(queue lines[], int time_current
);
int time_used(customer* custPtr);
int empty(queue* qPtr);

// ************ Main Function ************ //
int main() {

    int test_cases;
    FILE *fp = fopen("assignment2input.txt", "r");

    // read number of testcases
    fscanf(fp, "%d", &test_cases);

    for (int i=0; i < test_cases; i++) {

        // Read number of customers
        int number_customers;
        fscanf(fp, "%d", &number_customers);

        // Create array of queues of lines
        queue lines[LINES];
        // Init the queue
        for (int i=0; i<LINES; i++)
            initQueue(&lines[i]);

        // Read data
        for (int i=0; i<number_customers; i++) {

            // Read customers data 
            char name[MAX_Namesize+1];
            int time, line, num_items;
            fscanf(fp, "%d%d%s%d", &time, &line, name, &num_items);

            // Create struct for customer
            customer* tmpPtr = createNode_customer(name, time, line, num_items);

            customers_list* tmpNode = malloc(sizeof(customers_list));
            tmpNode->customerPtr = tmpPtr;
            tmpNode->next = NULL;

            // enqueue 
            enqueue(&lines[line-1], tmpNode);
        }
        // initialize current time 
        int time_current = 0;
        for (int i = 0; i < number_customers; i++) {

            // choose line priority
            int chooseLine = linePriority(lines, time_current);
            customers_list* tmpNode = dequeue(&lines[chooseLine]);
            customer* tmpPtr = tmpNode->customerPtr;

            // update time counter
            if (time_current < tmpPtr->time)
            {
              time_current = tmpPtr->time;
            }
            time_current += time_used(tmpPtr);
            // Output description to console
            printf("%s from line %d checks out at time %d.\n", tmpPtr->name, tmpPtr->line_number, time_current
            );
            free_node(tmpNode);
        }
    }
    fclose(fp);
    return 0;
}
// **********************  Functions ********************** //
int time_used(customer* custPtr) {

  int result;
  result = NUM_OF_SECONDS + time_processItem * custPtr->num_items;

  return result;
} // end function time_used

void initQueue(queue* qPtr) {
    qPtr->front = NULL;
    qPtr->back = NULL;
} // end function initQueue

//  FROM LAB 5 
void enqueue(queue* qPtr, customers_list* newNode) {

    
    if (empty(qPtr)) {
        qPtr->front = newNode;
        qPtr->back = newNode;
    }
    else {
        qPtr->back->next = newNode;
        qPtr->back = newNode;
    }
} // end fnction enqueue

int empty(queue* qPtr) {
    return qPtr->front == NULL;
} // end function empty

customer* front_customer(queue* qPtr) {
    return qPtr->front->customerPtr;
} // end function front_customer

customers_list* dequeue(queue* qPtr) {

    customers_list* retVal = qPtr->front;

    qPtr->front = qPtr->front->next;

    if (qPtr->front == NULL)
        qPtr->back = NULL;

    return retVal;
} // end function dequeue

void free_node(customers_list* ptrNode) {
    free(ptrNode->customerPtr);
    free(ptrNode);
} // end function free_node

customer* createNode_customer(char* name, int time, int line, int num_items) {
    customer* tempNode = malloc(sizeof(customer));
    strcpy(tempNode->name, name);
    tempNode->time = time;
    tempNode->line_number = line;
    tempNode->num_items = num_items;
    return tempNode;
} // end function createNode_customer

int linePriority(queue lines[], int time_current
) {
    int result = -1, minItems = max_total_items+1;
    
    for (int i=0; i<LINES; i++) {

        if (empty(&lines[i])) 
          continue;

        customer* tmp = front_customer(&lines[i]);

        if (tmp->time > time_current) 
          continue;

        if (tmp->num_items < minItems) {
            result = i;
            minItems = tmp->num_items;
        }
    }

    if (result != -1) 
      return result;

    int the_Time = TIME + 1;
    for (int i=0; i<LINES; i++) {

        if (empty(&lines[i])) 
          continue;

        customer* tmp = front_customer(&lines[i]);

        if (tmp->time < the_Time) {
            result = i;
            the_Time = tmp->time;
        }
    }

    return result;
} // end function linePriority