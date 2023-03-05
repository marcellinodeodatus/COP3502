// --36-- read the instruction provided above before starting  --36--
// Write your name here: Deodatus Marcellino
// your UCFID: 4411106

#include<stdio.h>
#include <stdlib.h>
 typedef struct node{
    int info;
    struct node *next;
}node;

node* SortInsert(node *root, int item); //this function is complete
void simplePrint(node* root); //this function is complete
int sumMyList(node* root); //you have to write this function, see bellow //total grade 50
node* BackToFrontMove (node * root); //you have to write this function, see bellow // total grade 50




int main()
{
    node* head=NULL;
    node* head2 = NULL;

    node *t;
    int ch,ele;
    head = SortInsert(head, 4);
    head = SortInsert(head,6);
    head = SortInsert(head,3); 
    head = SortInsert(head,5);

    printf("\nSimple print List 1: ");
    simplePrint(head);

     printf("\nsum of the list %d", sumMyList(head)); //modify the sumMyList function to make it work. It should print 18. 

    head  = BackToFrontMove(head);//modify the BackToFrontMove function to make it work
    printf("\nSimple print: "); //it should print 6, 3, 4, 5
    simplePrint(head);


    return 0;

}

void simplePrint(node* root)
{
    node* t=root;
    while(t!=NULL)
    {
        printf("%d ",t->info);
        t=t->next;
    }
}

node*  SortInsert(node* root, int item)
{
    node *temp;
    node *t;
    temp= (node *) malloc(sizeof(node));
    temp->info=item;
    temp->next=NULL;
    if (root==NULL || root->info >=item)
    {
            temp->next = root;
            root = temp;
    }
    else
    {
         t = root;
         while (t->next != NULL && t->next->info <item)
                   t = t->next;
         temp->next = t->next;
         t->next = temp;
    }

    return root;
}

///////// All questions are starting here//////////////////


int sumMyList(node* root)
{
  /*this function takes the head of a linked list and return the sum of all the data in the linked list. You can use for loops or recursion. 
    */
  node* temp = root;
  static int total = 0;

  total += temp->info;

  if (temp->next != NULL){
    sumMyList(temp->next);
    
  }

  return total;
};


node* BackToFrontMove (node * root)
{
    /*this function takes the head of a linked list and move the tail node's item in the linked list to the head
    and return the new head. Example: Linked list 3, 4, 5, 6 will be changed to 6, 3, 4, 5
    At the end, the function returns the head*/

  // if the list is empty
  if (root == NULL)
    return NULL;

  // if there is only one element in linked list
  if (root->next == NULL)
    return root;

  node* last = root;
  node* prev = NULL;

  // traverse the list 
  while (last->next != NULL)
  {
    prev = last;
    last = last->next;
  }

  // move the last item in the list to front
  prev->next = NULL;
  last->next = root;

    return last;

}