// linked_list_basic.c
// Implements a basic singly linked list in C with insertion at the head and print functionality.
#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node *next;
};

struct Node *head;

// Function to insert a new node at the beginning
// of the linked list
void Insert(int x)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = x;
  newNode->next = head;
  head = newNode;
}

void Print()
{
  struct Node *temp = head;
  printf("The linked list is: ");
  while (temp != NULL)
  {
    printf(" %d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
};

int main()
{
  head = NULL;
  printf("How many numbers?\n");
  int n, i, x;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    printf("Enter number\n");
    scanf("%d", &x);
    Insert(x);
    Print();
  }
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
  temp->data = 2;
  temp->next = NULL;
  head = temp;
  return 0;
}
