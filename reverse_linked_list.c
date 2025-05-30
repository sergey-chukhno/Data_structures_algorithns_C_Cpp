// reverse_linked_list.c
// Implements reversal of a singly linked list in C. Demonstrates iterative reversal algorithm.

#include <stdio.h>
#include <stdlib.h>
struct Node
{
  int data;
  struct Node *next;
};
struct Node *head; // global variable to store the head of the linked list

struct Node *Insert(struct Node *head, int data)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // allocate memory for new node
  newNode->data = data;                                              // assign data to the new node
  newNode->next = NULL;                                              // point the new node to NULL
  if (head == NULL)
  {
    head = newNode;
    printf("Inserted %d\n", data);
    return head;
  }
  struct Node *temp = head;
  while (temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = newNode;
  printf("Inserted %d\n", data);
  return head;
};

void Print(struct Node *head)
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
struct Node *Reverse(struct Node *head)
{
  struct Node *current, *prev, *next;
  current = head;
  prev = NULL;
  while (current != NULL)
  {
    next = current->next; // store the next node
    current->next = prev; // reverse the link
    prev = current;       // move prev to current
    current = next;       // move current to next
  }
  head = prev; // update the head to the new first node
  return head; // return the new head
};
int main()
{
  struct Node *head = NULL;
  head = Insert(head, 2);
  head = Insert(head, 3);
  head = Insert(head, 4);
  head = Insert(head, 5);
  Print(head);
  head = Reverse(head); // reverse the linked list
  Print(head);          // print the reversed linked list
  return 0;
}