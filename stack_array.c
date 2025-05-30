// stack_array.c
// Implements a stack using a fixed-size array in C. Supports push, pop, peek, and print operations.
#include <stdio.h>
#include <stdlib.h>
#define MAX 100 // maximum size of the stack
int stack[MAX]; // array to store stack elements
int top = -1;   // index of the top element in the stack
// function to check if the stack is empty
int isEmpty()
{
    return top == -1; // returns 1 if stack is empty, 0 otherwise
}
// function to check if the stack is full
int isFull()
{
    return top == MAX - 1; // returns 1 if stack is full, 0 otherwise
}
// function to push an element onto the stack
void push(int x)
{
    if (isFull())
    {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = x; // increment top and add element to stack
    printf("Pushed %d\n", x);
}
// function to pop an element from the stack
int pop()
{
    if (isEmpty())
    {
        printf("Stack underflow\n");
        return -1; // return -1 if stack is empty
    }
    return stack[top--]; // return top element and decrement top
}
// function to get the top element of the stack
int peek()
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        return -1; // return -1 if stack is empty
    }
    return stack[top]; // return top element
}
// function to print the stack
void printStack()
{
    if (isEmpty())
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= top; i++)
    {
        printf("%d ", stack[i]); // print elements from top to bottom
    }
    printf("\n");
}
// main function to test the stack implementation
int main()
{
    int choice, value;
    while (1)
    {
        printf("1. Push\n2. Pop\n3. Peek\n4. Print Stack\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value to push: ");
            scanf("%d", &value);
            push(value);
            break;
        case 2:
            value = pop();
            if (value != -1)
            {
                printf("Popped %d\n", value);
            }
            break;
        case 3:
            value = peek();
            if (value != -1)
            {
                printf("Top element is %d\n", value);
            }
            break;
        case 4:
            printStack();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
