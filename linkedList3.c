// This program implements a singly linked list in C. It allows the user to delete a node from the list at a specific position.

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
struct Node *head; // global variable to store the head of the linked list 
;
void Insert(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // allocate memory for new node
  newNode->data = data; // assign data to the new node
  newNode->next = NULL; // point the new node to NULL
  if (head == NULL) {
    head = newNode;
    printf("Inserted %d\n", data);
    return;
  }
  struct Node *temp = head;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
  printf("Inserted %d\n", data);
};

void Print() {
  struct Node *temp = head; 
  printf("The linked list is: ");
  while (temp != NULL) {
    printf(" %d ", temp->data);
    temp = temp->next;
  }
  printf("\n");
};

void Delete(int position) {
  struct Node *temp = head; 
  if (position == 1) { // if the first node is to be deleted
    head = temp->next; // head points to the second node
    free(temp); // free the memory of the deleted node
    printf("Node at position %d deleted\n", position);
    return;
  }
  int i;
  for (i = 0; i < position - 2; i++) {
    temp = temp->next; // temp points to the node before the one to be deleted
  };
  struct Node *nodeToDelete = temp->next; // note to be deleted 
  temp->next = nodeToDelete->next; // bypass the node to be deleted
  free(nodeToDelete); // free the memory of the deleted node
  printf("Node at position %d deleted\n", position);
};

  int main()
  {
    head = NULL;
    Insert(2);
    Insert(3);
    Insert(4);
    Insert(5);
    Print();
    int position;
    printf("Enter the position of the node to delete: ");
    scanf("%d", &position);
    Delete(position);
    Print();
  }