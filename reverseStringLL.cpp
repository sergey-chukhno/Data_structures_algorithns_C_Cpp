//Reversing a string using linked list 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

struct Node {
    char data;
    struct Node* next;
};
struct Node* head = NULL; // global variable to store the head of the linked list
void Insert(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // allocate memory for new node
    newNode->data = data; // assign data to the new node
    newNode->next = NULL; // point the new node to NULL
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}
void Print() {
    struct Node* temp = head;
    printf("The linked list is: ");
    while (temp != NULL) {
        printf(" %c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void Reverse() {
    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next; // Store next node
        current->next = prev; // Reverse the link
        prev = current; // Move prev to current
        current = next; // Move to next node
    }
    head = prev; // Update head to the new first node
}
void Delete(int position) {
    struct Node* temp = head;
    if (position == 1) { // if the first node is to be deleted
        head = temp->next; // head points to the second node
        free(temp); // free the memory of the deleted node
        return;
    }
    int i;
    for (i = 0; i < position - 2; i++) {
        temp = temp->next; // temp points to the node before the one to be deleted
    };
    struct Node* nodeToDelete = temp->next; // note to be deleted 
    temp->next = nodeToDelete->next; // bypass the node to be deleted
    free(nodeToDelete); // free the memory of the deleted node
}
int main() {
    head = NULL;
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    for (int i = 0; i < strlen(str); i++) {
        Insert(str[i]);
    }
    Print();
    Reverse();
    Print();
    return 0;
}
// This code reverses a string using a linked list. It first inserts each character of the string into the linked list, then reverses the linked list and prints the reversed string.
// The code uses a singly linked list to store the characters of the string. The `Insert` function inserts a new node at the end of the linked list, while the `Reverse` function reverses the linked list by changing the direction of the links between nodes. The `Print` function prints the contents of the linked list.
// The `Delete` function is included but not used in this example. It deletes a node at a specified position in the linked list.
// The code uses the `malloc` function to allocate memory for new nodes and the `free` function to deallocate memory for deleted nodes. It also uses the `struct` keyword to define a structure for the linked list nodes.
// It represents an iterative approach to reversing a string using a linked list. The code is written in C and uses standard input/output functions to read the string and print the reversed string.