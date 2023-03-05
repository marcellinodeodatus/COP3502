/* COP 3502 - Lab 4
** Name: Deodatus Marcellino
** Spring 2021
*/
#include <stdio.h>
#include <stdlib.h>
#define EMPTY -1

struct node {
        int data;
        struct node* next;
};

struct queue {
        struct node *front, *back;
};
 // ============= Functions prototype ================ //
void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue *qPtr);
int empty(struct queue *qPtr);
int front(struct queue* qPtr);
void displayQueue(struct queue* MyQueuePtr);

// =================== main ================ //
int main() {
  struct queue* MyQueuePtr = (struct queue*)malloc(sizeof(struct queue));
  init(MyQueuePtr);

  int choice;
  int data;
  int i;

  while (1)
  {
    printf("\n1.Insert element to queue\n");
    printf("\n2.Delete element from queue\n");
    printf("\n3.Display all elements of queue\n");
    printf("\n4.Quit\n");
    printf("\nEnter your choice: \n");
    scanf("%d", &choice);

    switch(choice)
    {
      case 1:
        printf("\nWhat data you want to put in the queue?: ");
        scanf("%d", &data);
        enqueue(MyQueuePtr, data);
        displayQueue(MyQueuePtr);
        break;
      case 2:
        data = dequeue(MyQueuePtr);

        if(data != EMPTY)
        {
          printf("\n%d deleted from queue\n", data);
          displayQueue(MyQueuePtr);
        }
        else{
          printf("Empty queue\n");
        }
        break;
      case 3:
        displayQueue(MyQueuePtr);
        break;
      case 4:
        exit(1);
      default:
        printf("Wrong choice \n");
    }
  }
  return 0;
}

// =========== Functions Here ============ //

void displayQueue(struct queue* MyQueuePtr)
{
  struct node* t = MyQueuePtr->front;
  while(t)
  {
    printf("%d ", t->data);
    t = t->next;
  }
}

void init(struct queue* qPtr) {
        qPtr->front = NULL;
        qPtr->back = NULL;
} // end function init

int enqueue(struct queue* qPtr, int val) {
        
  struct node* temp = (struct node*)malloc(sizeof(struct node));

  if(temp != NULL)
  {
    temp->data = val;
    temp->next = NULL;

    if(qPtr->back != NULL) {
      qPtr->back->next = temp;
    }

    qPtr->back = temp;

    if (qPtr->front == NULL)
    {
      qPtr->front = temp;
    }

    return 1;

  }
   else {
     return 0;
   }

} // end function enqueue

int dequeue(struct queue * qPtr)
{
  struct node* tmp;
  int retval;

  if (qPtr->front == NULL)
  {
    return EMPTY;
  }

  retval = qPtr->front->data;

  tmp = qPtr->front;

  qPtr->front = qPtr->front->next;

  if (qPtr->front == NULL){
    qPtr->back = NULL;
  }

  free(tmp);

  return retval;
}

int empty(struct queue* qPtr) {
  return qPtr->front == NULL;
}

int front (struct queue* qPtr)
{
  if (qPtr->front != NULL)
  {
    return qPtr->front->data;
  } else {
    return EMPTY;
  }
}