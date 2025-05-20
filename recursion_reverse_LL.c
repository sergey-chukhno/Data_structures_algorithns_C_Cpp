#include <stdlib.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
}; 

// Insert a new node at the end of the list
struct Node* Insert(struct Node* head, int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    if (head == NULL) {
        return temp;
    }
    struct Node* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = temp;
    return head;
}

// Print the linked list
void Print(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

struct Node* Reverse(struct Node *p) {
  if (p == NULL || p->next == NULL) {
    return p; // update the head to the new first node
  }
  struct Node* newHead = Reverse(p->next); // get the new head of the reversed list
  p->next->next = p; // reverse the link
  p->next = NULL; // set the next of the current node to NULL
  return newHead;
 } // return the new head
  

int main() {
  struct Node *head = NULL;
  head = Insert(head, 2); 
  head = Insert(head, 3);
  head = Insert(head, 4);
  head = Insert(head, 5);
  Print(head); 
  head = Reverse(head); // assign the new head
  Print(head); // print the reversed linked list
  return 0; 
}