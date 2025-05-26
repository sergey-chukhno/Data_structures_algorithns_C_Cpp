// Linked list implementation of a stack
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};
struct Node* top = NULL; // global variable to store the top of the stack

//For stack we always insert and delete at head 
// Function to create a new node
struct Node* getNewNode(int x) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}
// Function to push an element onto the stack 
void push(int x) {
    struct Node* newNode = getNewNode(x);
    newNode->next = top; // point the new node to the current top
    top = newNode; // update the top to the new node
    printf("Pushed %d\n", x);
}
// Function to pop an element from the stack
int pop() {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1; // return -1 if the stack is empty
    }
    struct Node* temp = top; // store the current top
    int poppedValue = temp->data; // get the data of the top node
    top = top->next; // update the top to the next node
    free(temp); // free the memory of the popped node
    printf("Popped %d\n", poppedValue);
    return poppedValue;
}
// Function to peek at the top element of the stack
int peek() {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1; // return -1 if the stack is empty
    }
    return top->data; // return the data of the top node
}
// Function to check if the stack is empty
int isEmpty() {
    return top == NULL; // return 1 if the stack is empty, 0 otherwise
}
// Function to print the stack
void printStack() {
    struct Node* temp = top; 
    printf("The stack is: ");
    while (temp != NULL) {
        printf(" %d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
// Function to delete the stack
void deleteStack() {
    while (top != NULL) {
        pop(); // pop all elements from the stack
    }
    printf("Stack deleted\n");
}
// Main function to test the stack implementation 
int main() {
    int choice, x;
    while (1) {
        printf("1. Push\n2. Pop\n3. Peek\n4. Print Stack\n5. Delete Stack\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &x);
                push(x);
                break;
            case 2:
                pop();
                break;
            case 3:
                x = peek();
                if (x != -1) {
                    printf("Top element is %d\n", x);
                }
                break;
            case 4:
                printStack();
                break;
            case 5:
                deleteStack();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}