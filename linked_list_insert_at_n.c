// linked_list_insert_at_n.c
// Implements a singly linked list in C with insertion at a specific position (nth node).

#include <stdlib.h>
#include <stdio.h>

struct Node
{
  int data;
  struct Node *next;
};

struct Node *head;

void Insert(int data, int n)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  if (n == 1)
  {
    newNode->next = head;
    head = newNode;
    return;
  }
  struct Node *temp = head;
  for (int i = 0; i < n - 2; i++)
  {
    temp = temp->next;
  }
  newNode->next = temp->next;
  temp->next = newNode;
};

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
  head = NULL;  // empty list
  Insert(2, 1); // insert number 2 at position 1
  Insert(3, 2); // insert number 3 at position 2
  Insert(4, 2); // insert number 4 at position 3
  Insert(5, 1); // insert number 5 at position 4
  Print();
}