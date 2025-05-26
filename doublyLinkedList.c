#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev; // pointer to the previous node
};
struct Node *head; // global variable to store the head of the linked list

struct Node* getNewNode(int x){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = x; 
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
void insertAtHead(int x) {
    struct Node* newNode = getNewNode(x);
    if (head == NULL) {
        head = newNode;
        return;
    }
    newNode->next = head; // point the new node to the current head
    head->prev = newNode; // point the current head's prev to the new node
    head = newNode; // update the head to the new node
    printf("Inserted %d\n", x);
}

void insertAtTail(int x) {
    struct Node* newNode = getNewNode(x);
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next; // traverse to the end
    }
    temp->next = newNode; // point the last node's next to the new node
    newNode->prev = temp; // point the new node's prev to the last node
    printf("Inserted %d\n", x);
}

// Function to print the linked list
// in forward order
void print(){
    struct Node *temp = head; 
    printf("The linked list is: ");
    while (temp != NULL) {
        printf(" %d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
};

// Function to delete a node at a given position
void deleteNode(int position) {
    struct Node *temp = head; 
    if (position == 1) { // if the first node is to be deleted
        head = temp->next; // head points to the second node
        free(temp); // free the memory of the deleted node
        return;
    }
    int i;
    for (i = 0; i < position - 2; i++) {
        temp = temp->next; // temp points to the node before the one to be deleted
    };
    struct Node *nodeToDelete = temp->next; // note to be deleted 
    temp->next = nodeToDelete->next; // bypass the node to be deleted
    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = temp; // update the prev pointer of the next node
    }
    free(nodeToDelete); // free the memory of the deleted node
};
// Function to print the linked list in reverse order
void reversePrint(){
    struct Node *temp = head;
    if (temp == NULL)
        return;
        // Traverse to the last node
    printf("The linked list in reverse order is: ");
    while (temp->next != NULL) {
        temp = temp->next;
    }
    // Print the linked list in reverse order
    while (temp != NULL) {
        printf(" %d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
};

int main() {
    head = NULL;
    insertAtHead(2);
    insertAtHead(3);
    insertAtHead(4);
    insertAtHead(5);
    insertAtTail(6);
    insertAtTail(7);
    print();
    reversePrint();
    deleteNode(3);
    print();
    deleteNode(1);
    print();
    return 0;
}