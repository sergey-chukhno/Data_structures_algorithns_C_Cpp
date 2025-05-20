#include <stdlib.h>
#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
}; 
struct Node* head; // global variable to store the head of the linked list

struct Node* Insert(struct Node* head, int data) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    if (head == NULL) {
        head = temp;
        printf("Inserted %d\n", data);
        return head; // return the new head
    } else {
        struct Node *temp1 = head;
        while (temp1->next != NULL) {
            temp1 = temp1->next; // traverse to the end
        }
        temp1->next = temp;
        printf("Inserted %d\n", data);
        return head;
    }
}

void
Print(struct Node *head)
{
  // print the linked list
  // 2 4 5 6
  if (head == NULL) {
    printf("\n");
    return;
  }
  printf("%d ", head->data);
  Print(head->next);
};

void ReversePrint(struct Node *head) {
  // recursion to print the linked list in reverse
  // 6 5 4 2
   if (head == NULL) {
    return;
  }
  ReversePrint(head->next); // first go to the end
  // then print the data
  // this will print the last node first
  printf("%d ", head->data);
}

int main() {
  struct Node *head = NULL;
  head = Insert(head, 2);
  head = Insert(head, 4);
  head = Insert(head, 5);
  head = Insert(head, 6);
  Print(head); // print the linked list
  printf("The linked list in reverse is: ");
  ReversePrint(head); // print the linked list in reverse 
  printf("\n");
  return 0;
}
