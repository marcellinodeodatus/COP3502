/* Lab Quiz 2
** Deodatus Marcellino
** COP 3502
** Spring 2021 
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
   int income, count;
   struct node *left, *right;
}node;

//*********** Function Prototype *********** //
void inorderTraversal(node *ptr, FILE * f);
void inorderTraversalOddNumber(node *root, FILE* f);
node* insert(node *, int a, int b);
node* findHighestIncome(node * ptr);

//********** Main ************** //
int main()
{
   node *root = NULL;
   node *ptr = NULL;   
   FILE *input = fopen("in.txt", "r");
   FILE *out = fopen("out.txt", "w");
   int N, income, count;

   if(input == NULL)
   {
       printf("Error: Cannot open file\n");
       exit(EXIT_FAILURE);
   }

   fscanf(input, "%d", &N);
   for(int i = 0; i < N; i++)
   {
       fscanf(input, "%d %d", &income, &count);
       root = insert(root, income, count);
   }

   fclose(input);

   // 2. Print the data in the tree in the in-order traversal to see the keys are in sorted order. Print them like comma separated tuple (income, count), (income, count),
   printf("Tree constructed from the file\n");
   printf("In-order: ");
   fprintf(out, "Tree constructed from the file\n");
   fprintf(out, "In-order: ");

   inorderTraversal(root, out);

   // 3. Write a function that prints all the incomes with odd number of people count.
   printf("\nIncomes with Odd number of people count:");
   fprintf(out, "\nIncomes with Odd number of people count: ");
   inorderTraversalOddNumber(root, out);
  printf("\n");
  fprintf(out,"\n");

    // 4.Write a function to find the total number of people having the highest income from your tree.    
   node* highestIncomenode = findHighestIncome(root);
   printf("Total number of people with the highest income: %d\n", highestIncomenode->count);
   fprintf(out, "Total number of people with the highest income: %d\n", highestIncomenode->count);
   fclose(out);
   return 0;
}

// **************** Functions ************* //
node* insert(node *root, int income, int count)
{
   if(root == NULL)
   {
       root = (node *)malloc(sizeof(node));
       root->income = income;
       root->count = count;
       root->left = root->right = NULL;
   }
   else
   if(income < root->income)
       root->left = insert(root->left, income, count);
   else
       root->right = insert(root->right, income, count);
   return root;
} // end function insert

void inorderTraversal(node *root, FILE * f)
{
   if(root != NULL)
   {
       inorderTraversal(root->left, f);
       printf("(%d, %d), ", root->income, root->count);
       fprintf(f,"(%d, %d), ", root->income, root->count);
       inorderTraversal(root->right, f);
   }
} // end function inorderTraversal

void inorderTraversalOddNumber(node *root, FILE* f){
   if(root != NULL)
   {
       inorderTraversalOddNumber(root->left, f);
       if (root->count % 2 != 0){
          printf("%d ", root->income);
          fprintf(f, "%d ", root->income);
       }
       inorderTraversalOddNumber(root->right, f);
   }
} // end function inorderTraversalOddNumber

node* findHighestIncome(node *root)
{
   if(root == NULL || root->right == NULL)
       return root;
   else
       return findHighestIncome(root->right);
} // end function findHighestIncome
